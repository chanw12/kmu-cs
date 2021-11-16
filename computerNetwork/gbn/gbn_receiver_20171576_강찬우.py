import select
import socket
import sys
from random import random


class Data(object):

    def __init__(self, msg, type, seq=0, state=0):
        self.msg = msg.decode()
        self.type = str(type)
        self.state = state
        self.seq = str(seq)

    def __str__(self):
        return self.seq + self.type + self.msg

class GBNreceiver:
    def __init__(self):
        self.nextseqnum = 1
        self.addr = ('127.0.0.1', 31500)
        self.sender_addr = ('127.0.0.1', 12345)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(self.addr)
        self.max_time = 5
        self.wait_time = 15
        self.number = 0
        self.N = 3
        self.buff_size = 1024
        self.send_windows = []

    def send(self, buffer):

        Timer = 0
        self.number = len(buffer)

        last_ack = 0
        ack_lock = 0
        msg_timer = 0
        ack_send = True
        while True:





            readable, writeable, errors = select.select([self.socket, ], [], [], 1)

            if len(readable) > 0:
                message, address = self.socket.recvfrom(self.buff_size)
                msg = message.decode()


                Timer += 1

                print('Receiver: msg를받음  ', msg[0])

                ackNum = int(msg[0])
                if ack_lock == ackNum:
                    ack_send = True
                msg_timer = 0

                if last_ack == ackNum-1 and ack_send :

                    if (random() < 0.2 ):
                        print('Receiver: 소켓 분실', int(ackNum))
                        last_ack = ackNum
                        ack_send = False
                        ack_lock = last_ack
                        continue
                    if random() < 0.1:
                        print('Receiver: ACK를잃어버림 ', int(ackNum)+1)
                        if ack_send ==True:
                            last_ack = ackNum

                        continue
                    self.socket.sendto(str(Data(''.encode(), 1, ackNum)).encode(), address)
                    print('Receiver: ACK보내기 ', int(ackNum)+1)
                    last_ack = ackNum
                else:
                    print('Receiver: 받은msg가 필요없다，현재 받은 가장큰ACK보내기 ', ack_lock)
                    self.socket.sendto(str(Data(''.encode(), 1, ack_lock-1)).encode(), address)
            else:

                Timer += 1
                msg_timer += 1

    def start(self):

        buffer = []
        while True:

            readable, writeable, errors = select.select([self.socket, ], [], [], 1)
            if (len(readable) > 0):
                message, address = self.socket.recvfrom(self.buff_size)
                if message.decode() == '-testgbn':
                    self.send(buffer)

s = GBNreceiver()
s.start()