import sys
import time 
import serial 
import signal
import traceback
from pyfirmata import Arduino, util



# create a PyMata instance
board = Arduino('/dev/ttyACM99')
serial_device = '/dev/ttyACM0'

it=util.Iterator(board)
it.start()

board.digital[11]._set_mode(0) # 0 is mode
board.digital[11].enable_reporting()

buffer=[0]*10

read11=board.digital[11].read

while read11() is None: pass



while True:
    value1=read11()
    print value1

