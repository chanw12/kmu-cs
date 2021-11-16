from socket import *
from select import *
from multiprocessing import Process, Queue
import random
import time
import math

def Application(id,queue):
    receiveData = queue.get()
    print(f"Application: 데이터 수신:{receiveData}")
    print("수신확인")
    return
def Transport(id,queue):
    #데이터 받는 부분
    receiveData = queue.get()
    print(f"Transport: 데이터 수신:{receiveData}")
    queue.put(receiveData)
    print(f"Transport: 데이터 전송 Transport -> Application : {receiveData}")
    print(f"Trnasport(S & W Protocol): ACK 생성")
    th10 = Process(target=Application, args=(10, queue))
    th10.start()
    th10.join()




    queue.put('010000010100001101001011')
    print(f"Transport: ACK 전송 Transport -> Network : 010000010100001101001011")


    return

def Network(id,queue):
    receiveData = queue.get()
    print(f"Network: 데이터 수신:{receiveData}")
    queue.put(receiveData)
    print(f"Network: 데이터 전송 Network -> Transport : {receiveData}")
    th9 = Process(target=Transport, args=(2, queue))
    th9.start()
    th9.join()





    receiveData = queue.get()
    print(f"Network: ACK 수신:{receiveData}")
    queue.put(receiveData)
    print(f"Network: ACK 전송 Network -> Datalink : {receiveData}")


def Datalink(id,queue):
    receiveData = queue.get()
    print(f"Datalink: 데이터 수신:{receiveData}")
    print("Datalink: Simple Protocol")
    unstuffing = receiveData.find('11111')
    temp = 0
    start = 0
    number1 = ""
    while unstuffing != -1:
        start = 0
        temp = receiveData.index('11111')
        number1 += receiveData[int(start):int(temp)]
        number1 += '11111'
        temp += 6
        start = temp
        receiveData = receiveData[int(start):len(receiveData)]
        unstuffing = receiveData.find('11111')
    number1 += receiveData #number1은 bit-unstuffnig 을 마친 데이터
    print(f'Datalink: message bit-unstuffing {number1}')
    queue.put(number1)
    print(f"Datalink: 데이터 전송 Datalink -> Network : {number1}")

    th8 = Process(target=Network, args=(8, queue))
    th8.start()
    th8.join()





    receiveData = queue.get()
    stuffing = receiveData.find('11111')
    print(f"Datalink:ACK 수신{receiveData}")
    temp = 0
    start = 0
    number1 = ''
    while (stuffing != -1):
        start = 0
        temp = receiveData.index('11111')
        number1 += receiveData[int(start):int(temp)]
        number1 += '111110'
        temp += 5
        start = temp
        receiveData = receiveData[int(start):len(receiveData)]
        stuffing = receiveData.find('11111')
    number1 += receiveData
    print(f"Datalink:ACK 전송 Datalink -> Physical: {number1}")
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

        if busy > 9:  # 이상적인 상황을 위해 busy를 9이상 나와야 뜨게 설정하였습니다
            print("CSMA/CD:busy")
            continue
        else:
            busy = 1
            print("CSMA/CD:Transmit and receive...")
            if ing == 0 or collision == 0:
                if collision == 3:  # 이상적으로 collision이 발생하지 않았다고 가정
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
    queue.put(number1)

    return

def Physical(id,queue):
    HOST = ''
    PORT = 10000
    BUFSIZE = 1024
    ADDR = (HOST, PORT)

    # 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM)

    # 소켓 주소 정보 할당
    serverSocket.bind(ADDR)
    print('bind')

    # 연결 수신 대기 상태
    serverSocket.listen(100)
    print('listen')
    # 연결 수락
    clientSocekt, addr_info = serverSocket.accept()


    # 클라이언트로부터 메시지를 가져옴
    data = clientSocekt.recv(65535)
    data = data.decode()
    print(f'Physical: sender-> receiver 데이터 수신  {data}')

    # reverse mlt-3 scheme
    arr = ''
    for i in range(0,len(data)):
        if i==0 and data[i] == '+':
            arr += '1'
            continue
        if i==0 and data[i] == '0':
            arr  += '0'
            continue
        if data[i] != data[i-1]:
            arr += '1'
        else:
            arr += '0'
    print(f'Physical: Reverse MLT-3 scheme {arr}')
    queue.put(arr)

    print(f"Physical: 데이터 전송 Physical -> Datalink : {arr}")
    th7 = Process(target=Datalink, args=(7, queue))
    th7.start()
    th7.join()




    receiveData = queue.get()
    print(f"Physical: ACK 수신: {receiveData}")
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

    clientSocekt.send(arr2.encode())
    print(f'Physical: Multi-transition MLT-3 scheme {arr2}')

    # 소켓 종료
    clientSocekt.close()
    serverSocket.close()
    print(f'Physical: ACK 전송 receiver -> sender : {arr2}')
    return


if __name__ == "__main__":
    queue = Queue()
    th6 = Process(target = Physical,args=(6,queue))
    th6.start()
    th6.join()
