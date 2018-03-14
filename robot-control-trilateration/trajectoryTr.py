import re
import numpy as np
import matplotlib.pyplot as plt

my_drill_site = [0, 0]
points_true = []
my_points = []
index = 0
mission_1 = None
mission_2 = None
mission_3 = None
stage = 1

with open("dots.txt") as txt:
    for line in txt:
        re.sub('\n', '', line)
        pair = line.split(" ")
        pair = [float(numb) for numb in pair]
        if len(pair) == 4:
            my_drill_site[0] = pair[0]
            my_drill_site[1] = pair[1]
            my_points.append(pair[2:])
        else:
            my_points.append(pair)
        index += 1

with open("../log/data2.csv") as txt:
    for line in txt:
        pair = line.split(";")
        pair = [float(numb) for numb in pair]
        if stage == 2:
            if mission_1 is None and pair[12] == 1:
                mission_1 = pair[0:2]
            if mission_2 is None and pair[13] == 1:
                mission_2 = pair[0:2]
            if mission_3 is None and pair[14] == 1:
                mission_3 = pair[0:2]
        if stage == 1:
            if mission_1 is None and pair[7] == 1:
                mission_1 = pair[0:2]
        points_true.append(pair)

if stage == 1:
    points_true = np.array(points_true)
    my_points = np.array(my_points)
    plt.figure(1)
    plt.subplot(121)
    plt.plot(points_true[:, 0], points_true[:, 1], color='green')
    plt.subplot(122)
    plt.plot(my_points[:, 0], my_points[:, 1], color='red')
    plt.show()


else:
    points_true = np.array(points_true)
    my_points = np.array(my_points)
    plt.figure(1)
    plt.subplot(211)
    plt.plot(points_true[:, 0], points_true[:, 1], color='green')
    plt.subplot(212)
    plt.plot(my_points[:, 0], my_points[:, 1], color='red')
    plt.show()
