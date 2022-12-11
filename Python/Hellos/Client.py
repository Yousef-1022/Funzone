import socket, select
import sys
# OS: Linux


class Client:
    
    def __init__(self):
        
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = ('localhost', 8080)
        self.connections = [sys.stdin, self.client]
    
    def run(self):
            
        print(f'Connecting to address: {self.server_address[0]} , port: {self.server_address[1]}')
        self.client.connect(self.server_address)
        
        while True:
            readers, _, _ = select.select(self.connections, [], [])
           
            for reader in readers:
        
                if reader is (self.client):
                    
                    data = reader.recv(1024).decode()
                    if data:
                        print("Server: {}".format(data))
                    else:
                        print("Server shutdown, closing client!")
                        sys.exit(0)
                elif reader is sys.stdin:
                
                    message = sys.stdin.readline() 
                    (self.client).send((''.join(message.splitlines())).encode())
           
                    
if __name__ == '__main__':
    user = Client()
    user.run()
    
# python3 Client.py