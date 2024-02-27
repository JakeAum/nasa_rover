# Jacob Auman
# 2-26-24
# NASA COSG Rover

# This program will help debug an array of ultrasonic sensors by visualizing the data in real time. 

import matplotlib.pyplot as plt
import numpy as np
import serial

def test_serial():
    # write random data values to serial
    # serial.write(b'1 2 3 4 5 6 7\n')
    pass

def serial_setup():
    # Set up the serial connection
    # serial.Serial('COM3', 9600)
    # serial.write(b'####### Initialized Sucessfully #######\n')
    pass
    

def get_serial_data():
    # Get the data from the serial connection
    data_raw = serial.readline()
    if data_raw == b'':
        data = [0, 0, 0, 0, 0, 0, 0]
    else:
        data = data_raw.split()
    # return data
    pass

def polar_graph(data):
    # Set Sensor array angles and width
    angles_deg = [ 45, 60, 75, 90, 105, 120, 135 ]  # Set the angles of each sensor. NOTE: 90 is directly in front of the rover
    angles_rad = np.deg2rad(angles_deg)
    width = np.deg2rad(13)  # Set the width of each sensor

    # Create a polar bar chart
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    ax.bar(angles_rad, data, width=width, alpha=0.75)  # Ensure data is in a list
    
    # Set the desired range of the polar graph
    ax.set_thetamin(30)  # Set the minimum angle
    ax.set_thetamax(150)  # Set the maximum angle
    
    # Increase the scale of the figure slightly
    fig.set_size_inches(8, 8)  # Adjust the figure size as desired
    
    plt.show()


def main():
    # test_serial()
    # data = get_serial_data()
    data = [1, 2, 2, 4, 5, 3, 2]
    polar_graph(data)


if __name__ == "__main__":
    serial_setup()
    main()

