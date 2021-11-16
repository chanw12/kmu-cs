import socket
import threading
from threading import *
import math
from multiprocessing import Process, Queue
import random
from multiprocessing import Process

import sys
import time
from socket import *

HOST = '127.0.0.1'
PORT = 10000
BUFSIZE = 1024
ADDR = (HOST,PORT)

clientSocket = socket(AF_INET, SOCK_STREAM)



def Application(id,receive):
    s = "1111100011111000"
    print(f"Application: 데이터 생성: {s} ")
    print("Application: 데이터 전송 APP -> Trans")
    receive.put(s)
    th2 = Process(target=Transport, args=(2, receive))
    th2.start()
    th2.join()
    print(f"Application: 데이터 {s} 전송/수신 완료")



def Transport(id, receive):

    receiveData = receive.get()
    print(f"Trnasport : 데이터 수신 {receiveData}")
    th3 = Process(target=Network,args =(3,receive))
    receive.put(receiveData)
    print(f"Transport: 데이터 전송 Transport -> Network:{receiveData}")

    print(f"Transport: S&W Protocol ,  ACK 수신대기...")

    th3.start()
    th3.join()





    receiveData = receive.get()
    if(receiveData =='010000010100001101001011' ):
        print(f"Transport: ACK 수신:{receiveData}")
        print("Trnasport: ACK가 성공적으로 수신되었습니다")


    return

def Network(id,receive):
    receiveData = receive.get()
    print(f"Network: 데이터 수신:{receiveData}")
    receive.put(receiveData)
    print(f"Network: 데이터 전송 Network -> Datalink{receiveData}")
    th4 = Process(target=Datalink, args=(4, receive))
    th4.start()
    th4.join()

    receiveData = receive.get()
    print(f"Network: ACK 수신:{receiveData}")
    receive.put(receiveData)
    print(f"Network: ACK 전송 Network -> Transport : {receiveData}")

    return


def Datalink(id,receive):
    data = receive.get()
    stuffing = data.find('11111')
    print(f"Datalink:데이터 수신{data}")
    temp = 0
    start = 0
    number1 = ''
    while (stuffing != -1):
        start = 0
        temp = data.index('11111')
        number1 += data[int(start):int(temp)]
        number1 += '111110'
        temp += 5
        start = temp
        data = data[int(start):len(data)]
        stuffing = data.find('11111')
    number1 += data


    print(f"Datalink:데이터 전송 Datalink -> Physical{number1}")
    print(f"Datalink: Simple Protocol ")
    attemptnum = 0
    collision = 0
    busy = random.randrange(0, 10)
    transmit = False
    max_Attempt = 15
    print(f"CSMA/CD: Attempt {attemptnum}")
    while attemptnum < max_Attempt:
        collision = random.randrange(0, 2)
        if busy != 1:
            busy = random.randrange(0, 10)
        ing = random.randrange(0, 8)

        if busy > 9: # 이상적인 상황을 위해 busy를 9이상 나와야 뜨게 설정하였습니다
            print("CSMA/CD:busy")
            continue
        else:
            busy = 1
            print("CSMA/CD:Transmit and receive...")
            if ing == 0 or collision == 0:
                if collision == 3: #이상적으로 collision이 발생하지 않았다고 가정
                    print("CSMA/CD:Collision deteceted")
                    attemptnum = attemptnum + 1
                    if attemptnum < max_Attempt:
                        print("CSMA/CD:Send a jammaing signal")
                        num2 = math.pow(2, attemptnum)
                        waittime = random.randrange(0, int(num2) - 1)
                        print(f"CSMA/CD:wait {waittime} ms")
                        time.sleep(0.001 * waittime)
                        print(f"CSMA/CD: Attempt{attemptnum}")
                        busy = 0
                    continue
                else:
                    print("CSMA/CD:Transmit Success")
                    transmit = True
                    break
            else:
                continue
    if (transmit == False):
        print("CSMA/CD:Transmit Fail")
    receive.put(number1)
    th5 = Process(target=Physical, args=(5, receive))
    th5.start()
    th5.join()



    data = receive.get()
    print(f'Datalink: ACK 수신 : {data}')

    unstuffing = data.find('11111')
    temp = 0
    start = 0
    number1 = ""
    while unstuffing != -1:
        start = 0
        temp = data.index('11111')
        number1 += receiveData[int(start):int(temp)]
        number1 += '11111'
        temp += 6
        start = temp
        receiveData = receiveData[int(start):len(receiveData)]
        unstuffing = receiveData.find('11111')
    number1 += data  # number1은 bit-unstuffnig 을 마친 데이터
    print(f'Datalink: message bit-unstuffing : {number1}')
    receive.put(number1)
    print(f"Datalink: 데이터 전송 Datalink -> Network : {number1}")

    return

def Physical(id,receive):
    receiveData = receive.get()
    print(f"Physical: 데이터 수신 {receiveData}")
    arr2 = ''
    for i in range(0, len(receiveData) - 1):
        if i == 0 and receiveData[0] == '0':
            arr2 += '0'
        if i == 0 and receiveData[0] == '1':
            arr2 += '+'
        if receiveData[i + 1] == '0':
            arr2 += arr2[i]
            continue
        if receiveData[i + 1] == '1' and arr2[i] != '0':
            arr2 += '0'
            continue
        if receiveData[i + 1] and arr2[i] == '0':
            findNon = False
            for j in range(0, arr2.__len__()):
                if arr2[j] == '+':
                    findNon = True
                if arr2[j] == '-':
                    findNon = False

            if findNon:
                arr2 += '-'
            else:
                arr2 += '+'
    print(f'Physical: Multi-transition MLT-3 scheme: {arr2}')
    try:
        clientSocket.connect(ADDR)  # 서버에 접속을 시도한다.
        print(f'Physical: 데이터 전송 sender -> receiver')
        clientSocket.send(arr2.encode())  # 서버에 메시지 전달
    except  Exception as e:
        print('%s:%s' % ADDR)
        sys.exit()



    data = clientSocket.recv(2322)
    data = data.decode()
    print(f"Physicla: ACk 수신 {data}")

    arr = ''
    for i in range(0, len(data)):
        if i == 0 and data[i] == '+':
            arr += '1'
            continue
        if i == 0 and data[i] == '0':
            arr += '0'
            continue
        if data[i] != data[i - 1]:
            arr += '1'
        else:
            arr += '0'
    print(f'Physical: Reverse MLT-3 scheme : {arr}')

    receive.put(arr)
    print(f"Physical: ACk 전송 Physical -> Datalink {arr}")

    return


if __name__ == "__main__":
    ApptoTrans = Queue()
    th1 = Process(target=Application, args=(1,ApptoTrans))
    th1.start()
    th1.join()






