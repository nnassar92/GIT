def encoder_n():
    import sys
    import time 
    import serial 
    import signal
    import traceback
    from pyfirmata import Arduino, util
    import math
    
    diameter,pi=0.07239,3.14159265359
    
    # create a PyMata instance
    board = Arduino('/dev/ttyACM99')
    serial_device = '/dev/ttyACM0'
    
    it=util.Iterator(board)
    it.start()
    
    board.digital[11]._set_mode(0) 
    board.digital[11].enable_reporting()
    
    buff=[0.0]*10
    
    read11=board.digital[11].read
    
    while read11() is None: pass
    
    stime=time.time()
    
    buff[0]=0.0
    
    while True:
        value1=read11()
        stime=time.time()
        
        for i in range(9):
            value2=read11()
            if value2 is not value1:
                value1=value2
                buff[i+1]=time.time()-stime
                speed=pi*diameter/4.0/(buff[i+1]-buff[i])
       		
 		               
            
