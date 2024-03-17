import numpy as np
from ultrasonic_visualizer import polar_graph


# Test case 1: All sensors have the same data
try:
    data1 = [113, 0, 115, 117, 73, 80, 30]
    polar_graph(data1)
except Exception as e:
    print(f"Error in test case 1: {e}")

# Test case 2: Different data for each sensor
try:
    data2 = [5, 10, 15, 20, 15, 10, 5]
    polar_graph(data2)
except Exception as e:
    print(f"Error in test case 2: {e}")

# Test case 3: Empty data
try:
    data3 = []
    polar_graph(data3)
except Exception as e:
    print(f"Error in test case 3: {e}")

# Test case 4: Data with negative values
try:
    data4 = [-5, 0, 10, -15, 20, 5, -10]
    polar_graph(data4)
except Exception as e:
    print(f"Error in test case 4: {e}")

# Test case 5: Data with decimal values
try:
    data5 = [2.5, 5.7, 8.9, 3.2, 6.4, 9.6, 1.1]
    polar_graph(data5)
except Exception as e:
    print(f"Error in test case 5: {e}")