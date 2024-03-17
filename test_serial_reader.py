# Make sure VSCode serial monitor is off.
import serial.tools.list_ports
from time import sleep
import keyboard

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portsList = []

for onePort in ports:
    portsList.append(str(onePort))
    print(str(onePort))

val = input("Select Port: COM")

for x in range(0,len(portsList)):
    if portsList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portVar)

serialInst.baudrate = 9600
serialInst.port = portVar
serialInst.open()

sleep(1)
running = True

while running:
    if serialInst.in_waiting:
        packet = serialInst.readline()
        data = packet.decode('utf').rstrip('\n')
        print(data)
            
    if keyboard.is_pressed('esc'):
        running = False
        serialInst.close()
        break
        
