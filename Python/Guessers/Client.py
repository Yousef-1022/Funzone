from http import server
import socket
import sys
import time
import random
import math
# OS: Linux


class Client:
    
    def __init__(self):
        
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = ('localhost', 8080)
        self.low = 1
        self.high = 100
        self.guess = random.randint(1, 100)
        self.operator = random.choice(['<','>'])
    
    
    def make_guess (self, server_message) -> str:
        
        if(server_message == 'Yes'):    
            
            if(self.operator == '>'):   # > 21 , yes
                
                self.low = self.guess
                self.guess = math.floor((self.low + self.high)/2)

            else:                       # < 21 , yes
                self.high = self.guess
                self.guess = math.floor((self.low + self.high)/2)
                  
        else:
            
            if(self.operator == '>'):   # > 21 , no
                
                self.high = self.guess
                self.guess = math.floor((self.low + self.high)/2)
                
            else:                       # < 21 , no
                self.low = self.guess
                self.guess = math.floor((self.low + self.high)/2)
        
        self.operator = random.choice(['<','>'])
        
        if ((self.high - self.low)) == 1:
            self.operator = '='
            self.guess = random.choice([self.high,self.low])
        return self.operator + " " + str(self.guess)
                
    
    def run(self):
            
        print(f'Connecting to address: {self.server_address[0]} , port: {self.server_address[1]}')
        self.client.connect(self.server_address)
        client_message = (self.operator + " " + str(self.guess))
        (self.client).send(client_message.encode())
        print("Sent:",client_message)
        
        while True:
             
            data = self.client.recv(1024).decode()
            
            if data:
                
                if(data == 'NoEnd' or data == 'YesEnd'):
                    print("Received flag from server that someone won the game, disconnecting!")
                    sys.exit(1)
                
                else:
                    print("Server: {}".format(data))
                
                    if(data == 'End' or data == 'You Lose' or data == 'You Win'):
                        sys.exit()
                    else:
                        client_message = self.make_guess (data)
                        print("Sent:",client_message)
                        (self.client).send(client_message.encode())
            
            else:
                print("Server has shutdown, disconnecting!")
                sys.exit(1)
            time.sleep(random.randint(1, 5))
           
                    
if __name__ == '__main__':
    user = Client()
    user.run()
    
# python3 Client.py