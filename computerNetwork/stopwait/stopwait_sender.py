import socket
from threading import *
import random
import time
import struct


serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "localhost"
port = 8000
play = 1
serversocket.bind((host, port))

seqNum = 0
firstInWindow = -1
lastInWindow = -1
lastAcked = -1
numAcked = -1

class client(Thread):
    def __init__(self, socket, address):
        Thread.__init__(self)
        self.sock = socket
        self.addr = address
        self.start()

    def run(self):
        r = input("Send data -->")
        k='9'
        num = int(r.__len__())
        for i in range(0,num):
            rand = random.randrange(1, 11)
            while rand >9:
                clientsocket.send(k.encode())
                rand = random.randrange(1, 11)
                print(clientsocket.recv(1024).decode())
            clientsocket.send(r[i].encode())
            j=clientsocket.recv(1024).decode()
            while j == "9":
                time.sleep(2)
                print("ACK not Received")
                clientsocket.send(r[i].encode())
                j = clientsocket.recv(1024).decode()
            else:
                print(j)
        print('close')
        play = 0
        return






serversocket.listen(100)
print('Sender ready')
while (play):
    clientsocket, address = serversocket.accept()
    print("Receiver connected")
    client(clientsocket, address)
