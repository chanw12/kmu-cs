import socket
from threading import *

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "localhost"
port = 8000

serversocket.bind((host, port))


class sender(Thread):
    def __init__(self, socket, address):
        Thread.__init__(self)
        self.sock = socket
        self.addr = address
        self.start()

    def run(self):
        while 1:
            r = input("Send data -->")
            sendersocket.send(r.encode())
            print(sendersocket.recv(1024).decode())


serversocket.listen(100)
print('Sender ready')
while (True):
    sendersocket, address = serversocket.accept()
    print("Receiver  connected")
    sender(sendersocket, address)
