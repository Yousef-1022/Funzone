import socket
import select
import queue
import sys
import random
# OS: Linux


class Server:
    
    def __init__(self, address='localhost', port=8080):
        
        self.timeout = 0
        self.server_address = (address, port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
        self.server.bind(self.server_address)
        self.server.listen()
        self.connections = [self.server]
        self.messages = queue.Queue()
        self.game_number = random.randint(1, 100)
        print("Server generated number: {}".format(self.game_number))
        
        
    def deal_with_socket_error(self, client, error):
        
        print(f'ERROR: {error}')
        self.connections.remove(client)
        
        
    def add_client(self):
        
        client, _ = self.server.accept()
        self.connections.append(client)
    
    
    def make_response (self, message) -> str:
        
        splitted = message.split()
        #print("SERVER GOT: {} , game_number: {}".format(splitted,self.game_number))
        given_operator = splitted[0]
        given_value = splitted[1]
        server_answer = 'You Lose'
        
        if (int(given_value) > self.game_number):
            if(given_operator == '<'):
                server_answer = 'Yes'
            elif (given_operator == '>'):
                server_answer = 'No'
                
        elif (int(given_value) < self.game_number):
            if(given_operator == '>'):
                server_answer = 'Yes'
            elif (given_operator == '<'):
                server_answer = 'No'
                
        else: #elif (int(given_value) == self.game_number):
            if given_operator == '=':
                server_answer = 'You Win'
            else:
                server_answer = 'No'
            
        return server_answer
      
      
    def remove_all_users (self):
      
      for i in self.connections[1:]:
          i.send('End'.encode())
          self.connections.remove(i)
          
      with (self.messages).mutex:
          (self.messages).queue.clear()
        
        
    def deal_with_messages(self, messages, writeable_connections):
        
        while True:
            
            try:
                client, client_message = messages.get_nowait()
                if client in writeable_connections:
                    
                    if(not client_message):
                        self.connections.remove(client)
                        print("a Client quit")  
                        
                    else: 
                        print('a Client: {}'.format(client_message)) 

                        server_message = self.make_response (client_message)
                        
                        if(server_message == "You Lose"):
                            client.send(server_message.encode())
                            self.connections.remove(client)
                            
                        elif(server_message == "You Win"):
                            client.send(server_message.encode())
                            self.connections.remove(client)
                            self.remove_all_users()
                            return True
                        
                        else:
                            client.send(server_message.encode())                   
            except queue.Empty:
                break
            
        return False
                   
            
    def run(self):
        
        while self.connections:
            
            readable_connections, writeable_connections, _ = select.select(self.connections, self.connections, [], self.timeout)
            
            for x in readable_connections:
                
                if x is self.server:
                    self.add_client()
                else:
                    try:
                        message = x.recv(1024).decode()
                        self.messages.put((x, message))
                    except socket.error as e:
                        self.deal_with_socket_error(x, e)
                        
            checker = self.deal_with_messages(self.messages, writeable_connections)
            
            if (checker):
                self.game_number = random.randint(1, 100)
                print("Server generated new number: {}".format(self.game_number))

            
            
if __name__=='__main__':
    server = Server()
    server.run()
    
# python3 Server.py