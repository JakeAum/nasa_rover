# Jacob Auman
# 2-26-24
# NASA COSG Rover

# This program will help debug an array of ultrasonic sensors by visualizing the data in real time. 
import serial.tools.list_ports

import matplotlib.pyplot as plt
import numpy as np

from time import sleep
import keyboard


def main():
    # Establish Serial Connection
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

    # Read In Serial Data
    sleep(1)


    ########################################
    # Prepare the Polar Bar Chart

    angles_deg = [ 45, 60, 75, 90, 105, 120, 135 ]  # Set the angles of each sensor. NOTE: 90 is directly in front of the rover
    angles_rad = np.deg2rad(angles_deg)
    width = np.deg2rad(13)  # Set the width of each sensor

    # Create a polar bar chart
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    
    
    max_range = 250  # Set the maximum range of the plot
    # TODO: Need to experimentally validate the max range of sensors
            
   
    while True:
        if serialInst.in_waiting:
            packet = serialInst.readline()
            dataRaw = packet.decode('utf').rstrip('\n')
            # Convert the string to a list of integers
            data = dataRaw.split(' ')
            # remove \r from the last element
            data[-1] = data[-1].rstrip('\r')
            
            # Check for improper data
            if data == [] or len(data) != 7:
                data = [0,0,0,0,0,0,0]
                print("Data Error -_-")

            # Convert each string in Data to an integer in the same list
            for i in range(len(data)):
                data[i] = int(data[i])

            # Invert the data using the max range value
            data = [max_range - x for x in data]

            # Plot the data
            ax.bar(angles_rad, data, width=width, alpha=0.75)  # Ensure data is in a list
            # Graph settings
            ax.set_thetamin(30)  # Set the minimum angle
            ax.set_thetamax(150)  # Set the maximum angle
            ax.set_ylim(0, max_range) # Set the maximum range of the plot
            fig.set_size_inches(8, 8)   # Increase the scale of the figure slightly
            # draw the plot
            plt.draw() 
            plt.pause(0.01) #is necessary for the plot to update for some reason
            ax.clear() #clear the plot
            

        if keyboard.is_pressed('esc'):
            serialInst.close()
            break
            

if __name__ == "__main__":
    main()


