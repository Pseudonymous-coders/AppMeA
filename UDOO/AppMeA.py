import neo, time
from m2x.client import M2XClient
from threading import Thread
from getDui import doMic
from checkActive import isActive
from math import fabs

killed = 0
APIKEY = "a3e04dc4b17ecb6574b7ae8c9198b3af" 
DEVICEID = "72d48c4b1b7c8999cd5b4128a1337ae4"
STREAM = "acc"
client = M2XClient(key=APIKEY)
device = client.device(DEVICEID)
stream = device.stream(STREAM)
accel = neo.Accel()
accel.calibrate()

def wasRestless():
        global killed
        while 1:
                restless = 0
                for x in range(15):
                        vals = accel.get()
                        if fabs(vals[0]) > 150:
                                restless += 1
                        if fabs(vals[1]) > 150:
                                restless += 1
                        if fabs(vals[2]) > 150:
                                restless += 1
                        time.sleep(1)
                if restless > 4:
                        print "Movement: "+str(restless)
                        stream.add_value(restless)
                if killed:
                        break
running = 0
while 1:
        if isActive():
                if not running:
                        killed = 0
                        print "Started"
                        restless = Thread(target=wasRestless)
                        mic = Thread(target=doMic)
                        restless.start()
                        mic.start()
                        running = 1
                        print "Finished start"
        else:
                if running:
                        print "Stopped"
                        killed = 1
                        running = 0
        time.sleep(1)
        print "hit bottom"
