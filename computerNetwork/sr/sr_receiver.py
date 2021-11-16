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

class SRreceiver:
    def __init__(self):
        self.nextseqnum = 1
        self.addr = ('127.0.0.1', 1000)
        self.sender_addr = ('127.0.0.1', 8000)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(self.addr)
        self.max_time = 3
        self.wait_time = 15
        self.N = 3
        self.M = 4
        self.buff_size = 1024
        self.send_windows = []
        self.receive_windows = []

    def send(self, buffer):

        Timer = []


        last_ack = 0
        msg_timer = 0

        while True:

            for index, item in enumerate(Timer):
                if item > self.max_time:
                    if self.send_windows[index].state != 2:
                        self.send_windows[index].state = 0
                        print('Receiver: 시간 초과가 발생하여 다시 패스하다', self.send_windows[index].seq)




            readable, writeable, errors = select.select([self.socket, ], [], [], 1)

            if len(readable) > 0:
                message, address = self.socket.recvfrom(self.buff_size)
                msg = message.decode()
                if msg[1] == '1':
                    ack_num = msg[0]

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
                                self.send_windows = self.send_windows[idx:] # 창 뒤로 이동
                                Timer = Timer[idx:]
                            break
                else:

                    for index, item in enumerate(Timer):
                        if self.send_windows[index].state != 2:
                            item += 1
                    print('Receiver: MSG 수신 = ', msg[0])
                    ackNum = int(msg[0])
                    msg_timer = 0
                    if last_ack == ackNum - 1:
                        if random() < 0.1:
                            print('Receiver: 패킷을 잃어버림', str(ackNum))

                            continue
                        if random() < 0.1:
                            print('Receiver: ACK를 잃어버림 ', str(ackNum))
                            last_ack = ackNum

                            continue
                        toRemove = []
                        self.socket.sendto(str(Data(''.encode(), 1, ackNum)).encode(), address)
                        print('Receiver: ACK전송 ', str(ackNum))

                        self.receive_windows.append(ackNum)
                        for i in range(self.M):
                            if (ackNum + i) not in self.receive_windows:
                                last_ack = ackNum + i - 1
                                break
                            else:
                                last_ack = ackNum + i
                                toRemove.append((ackNum + i))
                        for ele in toRemove:
                            self.receive_windows.remove(ele)
                    else:
                        if (ackNum) > (last_ack + 1 + self.M) and ackNum < last_ack and ackNum not in self.receive_windows:
                            print('Receiver: 지금 받을수 없는msg를 받았습니다', ackNum)
                            continue
                        elif ackNum >= last_ack and ackNum not in self.receive_windows:
                            self.receive_windows.append(ackNum)
                            self.socket.sendto(str(Data(''.encode(), 1, ackNum)).encode(), address)



            else:

                for index, item in enumerate(Timer):
                    if self.send_windows[index].state != 2:
                        Timer[index] = item + 1
                msg_timer += 1

    def start(self):

        buffer = []
        while True:
            readable, writeable, errors = select.select([self.socket, ], [], [], 1)
            if (len(readable) > 0):
                message, address = self.socket.recvfrom(self.buff_size)
                if message.decode() == '-testsr':
                    self.send(buffer)

s = SRreceiver()
s.start()