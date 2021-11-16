import socket
import time
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "localhost"
port = 8000
s.connect((host, port))

while 2:
    data = s.recv(1024).decode()
    if(data == '9'):

        time.sleep(2)
        str = "Time out"
        s.send(str.encode())
        print("packet not received")
    else:
        print("Received --> " + data)
        str = "Acknowledgement: Message Received"
        s.send(str.encode())

s.close()