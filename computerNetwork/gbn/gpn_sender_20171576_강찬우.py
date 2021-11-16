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

class GBNsender:
    def __init__(self):
        self.nextseqnum = 1
        self.addr = ('127.0.0.1', 12345)
        self.receiver_addr = ('127.0.0.1', 31500)
        self.max_time = 5
        self.wait_time = 15
        self.number = 0
        self.N = 3
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(self.addr)
        self.buff_size = 1024
        self.send_windows = []
        self.revData = ''

    def send(self, buffer):


        pkg_timer = 0
        self.number = len(buffer)

        last_ack = 0
        msg_timer = 0

        while True:

            if pkg_timer > self.max_time:
                resend = []
                for data in self.send_windows:
                    data.state = 0
                    resend.append(data.seq)
                if len(resend) > 0:
                    print('Sender: 시간초과', resend)


            while len(self.send_windows) < self.N:
                if (self.nextseqnum > self.number):
                    break

                data = Data(buffer[self.nextseqnum - 1], 0, seq=self.nextseqnum)
                self.send_windows.append(data)
                self.nextseqnum += 1


            if not self.send_windows:
                if pkg_timer > self.max_time and msg_timer > self.wait_time:
                    print('Sender: 전송완료')
                    break


            for data in self.send_windows:
                if not data.state:
                    print('Sender: 전송중 ', data.seq)
                    self.socket.sendto(str(data).encode(), self.receiver_addr)
                    data.state = 1


            readable, writeable, errors = select.select([self.socket, ], [], [], 1)

            if len(readable) > 0:
                message, address = self.socket.recvfrom(self.buff_size)
                msg = message.decode()


                pkg_timer = 0
                print('Sender: ACK받음 ', int(msg[0])+1)
                ack_num = msg[0]
                for i in range(len(self.send_windows)):
                    if ack_num == self.send_windows[i].seq:
                        self.send_windows = self.send_windows[i+1:]
                        break

            else:

                pkg_timer += 1
                msg_timer += 1

    def start(self):

        buffer = []
        with open('Sender.txt', 'rb') as f:
            while True:
                seq = f.read(500)
                if len(seq) > 0:
                    buffer.append(seq)
                else:
                    break
        self.socket.sendto('-testgbn'.encode(), self.receiver_addr)
        self.send(buffer)


c = GBNsender()
c.start()