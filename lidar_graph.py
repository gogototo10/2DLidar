from serial import Serial
import time
import matplotlib.pyplot as plt
import math
centerToSensorDistance=25
ser = Serial('COM9', 115200)  # 윈도우
count=0
while 1:
    anglist = []
    if ser.readable():
        res = ser.readline()

        distanlist=res.decode()[:len(res) - 1].split(',')
        for i in range(len(distanlist)-1):
            anglist.append(int(distanlist[i])+centerToSensorDistance)
    plt.cla()
    


    xlist = []
    ylist = []
    a = (360 / len(anglist))
    for i in range(0, len(anglist)):
        tempx = anglist[i] * math.cos(math.radians(a * (i + 1)))
        tempy = anglist[i] * math.sin(math.radians(a * (i + 1)))
        xlist.append(tempx)
        ylist.append(tempy)
    plt.scatter(xlist, ylist);
    plt.xlim([-1000, 1000])  # X축의 범위: [xmin, xmax]
    plt.ylim([-1000, 1000])  # Y축의 범위: [ymin, ymax]
    plt.pause(1)
    count=count+1


plt.show()

