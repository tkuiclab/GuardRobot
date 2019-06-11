# Installation
```bash
$ sudo apt-get install ros-kinetic-joy
$ sudo apt-get install ros-kinetic-move-base ros-kinetic-rosserial ros-kinetic-rosserial-arduino
```

# Startup
```bash
$ roscore
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
# Arduino default using /dev/ttyACM0.
# If occurs Permission denied w/ /dev/ttyACM0,
# chmod a+rw /dev/ttyACM0
$ roslaunch motion joy.launch
```
