# BARC & Nick
# 9/3/2015
# Threading

import sys
import time
import signal
import traceback
from pyfirmata import Arduino, util
import threading

# create a PyMata instance
board = Arduino('/dev/ttyACM99')
serial_device = '/dev/ttyACM0'

global tlock

class myThread(threading.Thread):
    def __init__(self,function,args):
        threading.Thread.__init__(self)
        self.function=function
        self.args=args
        self.killme=False
        
    def run(self):
        while not self.killme:
            self.func(self.args)

class car:   #car class that contains the variables that we want to change
    def __init__(self):
        e_bl=0
        e_br=0
        e_fl=0
        e_fr=0
        a_x=0
        a_y=0
        a_z=0
        yaw=0   


tlock=threading.Lock()

def signal_handler(sig, frame):
    for i in threads:
        i.killme=True
    sys.exit(0)

# Initialize encoder
board.digital[11]._set_mode(0) # 0 is mode
board.digital[11].enable_reporting()
board.digital[12]._set_mode(0) # 0 is mode
board.digital[12].enable_reporting()
board.digital[8]._set_mode(0) # 0 is mode
board.digital[8].enable_reporting()
board.digital[9]._set_mode(0) # 0 is mode
board.digital[9].enable_reporting()

BARC=car()

