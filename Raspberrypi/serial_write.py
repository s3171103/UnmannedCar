import serial
import RPi.GPIO as GPIO
import time

ser=serial.Serial("/dev/ttyACM0",9600)  #change ACM number as found from ls /dev/tty/ACM*


msg = b"10101010101015456456561564848949845615615615615615615615615615615665"
while True:


    ser.write(msg)


    time.sleep(0.03)
