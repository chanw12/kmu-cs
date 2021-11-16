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


class SRsender:
    def __init__(self):
        self.nextseqnum = 1
        self.addr = ('127.0.0.1', 8000)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.receiver_addr = ('127.0.0.1', 1000)
        self.socket.bind(self.addr)
        self.max_time = 3
        self.wait_time = 15
        self.num = 0
        self.N = 3
        self.M = 4
        self.buff_size = 1024
        self.send_windows = []
        self.receive_windows = []


    def send(self, buffer):

        Timer = []
        self.num = len(buffer)


        msg_timer = 0

        while True:
            for index, item in enumerate(Timer):
                if item > self.max_time:
                    if self.send_windows[index].state != 2:
                        self.send_windows[index].state = 0
                        print('Sender: Timeout resent ', self.send_windows[index].seq)


            while len(self.send_windows) < self.N:
                if (self.nextseqnum > self.num):
                    break

                data = Data(buffer[self.nextseqnum - 1], 0, seq=self.nextseqnum)
                self.send_windows.append(data)
                Timer.append(0)
                self.nextseqnum += 1


            if not self.send_windows:
                if not Timer and msg_timer > self.wait_time:
                    print('Sender:전송완료')
                    break


            for index, data in enumerate(self.send_windows):
                if not data.state:
                    print('Sender: 데이터를 전송중 ' + data.seq)
                    self.socket.sendto(str(data).encode(), self.receiver_addr)
                    data.state = 1
                    Timer[index] = 0



            readable, writeable, errors = select.select([self.socket, ], [], [], 1)

            if len(readable) > 0:
                message, address = self.socket.recvfrom(self.buff_size)
                msg = message.decode()
                if msg[1] == '1':
                    ack_num = msg[0]
                    print('Sender: ACK받았다 ',msg[0])
                    if(len(self.send_windows) == 0):
                        continue
                    if int(ack_num) < int(self.send_windows[0].seq):
                        continue
                    Timer[int(ack_num) - int(self.send_windows[0].seq)] = 0
                    for i in range(len(self.send_windows)):
                        if ack_num == self.send_windows[i].seq:
                            self.send_windows[i].state = 2
                            if i == 0:
                                idx = 0
                                flag = 1
                                for idx in range(len(self.send_windows)):
                                    if self.send_windows[idx].state != 2:
                                        flag = 0
                                        break
                                idx += flag
                                self.send_windows = self.send_windows[idx:]
                                Timer = Timer[idx:]
                            break

            else:

                for index, item in enumerate(Timer):
                    if self.send_windows[index].state != 2:
                        Timer[index] = item + 1
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
        self.socket.sendto('-testsr'.encode(), self.receiver_addr)
        self.send(buffer)


c = SRsender()
c.start()