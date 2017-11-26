import serial
import matplotlib.pyplot as plt
from drawnow import *

values = []

serialArduino = serial.Serial('/dev/tty.usbmodem1421', 9600)

def plotValues():
    plt.title('Serial value from Arduino')
    plt.grid(True)
    plt.ylabel('Temperature in Celsius')
    plt.xlabel('Time')
    plt.plot(values, 'rx-', label='values')
    plt.legend(loc='upper right')

for i in range(0,26):
    values.append(0)
    
while True:
    while (serialArduino.inWaiting()==0):
        pass
    print("readline()")
    valueRead = serialArduino.readline(500)

    try:
        valueInFloat = float(valueRead)
        print(valueInFloat)
        if valueInFloat <= 1024.0:
            if valueInFloat >= 0.0:
                values.append(valueInFloat)
                values.pop(0)
                drawnow(plotValues)
            else:
                print("Invalid! negative number")
        else:
            print("Invalid! too large")
    except ValueError:
        print("Invalid! cannot cast")
