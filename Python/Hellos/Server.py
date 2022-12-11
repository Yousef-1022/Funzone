import socket, select
import queue
import sys
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
        
        
    def deal_with_socket_error(self, client, error):
        
        print(f'ERROR: {error}')
        self.connections.remove(client)
        
        
    def add_client(self):
        
        client, _ = self.server.accept()
        self.connections.append(client)
        
        
    def deal_with_messages(self, messages, writeable_connections):
        
        while True:
            try:
                client, client_message = messages.get_nowait()
                if client in writeable_connections:
                    print('Client: {}'.format(client_message))       
                    message = sys.stdin.readline()
                    client.send(''.join(message.splitlines()).encode())
            except queue.Empty:
                break
            
            
    def run(self):
        
        while self.connections:
            
            readable_connections, writeable_connections, _ = select.select(self.connections, self.connections, [], self.timeout)
            
            for x in readable_connections:
                
                if x is self.server:
                    self.add_client()
                else:
                    try:
                        message = x.recv(1024).decode()
                        
                        if(not message):
                            print("Client quit")
                            self.connections.remove(x)
                        else:
                            self.messages.put((x, message))
                            
                    except socket.error as e:
                        self.deal_with_socket_error(x, e)
            self.deal_with_messages(self.messages, writeable_connections)
            
            
if __name__=='__main__':
    server = Server()
    server.run()
    
# python3 Server.py