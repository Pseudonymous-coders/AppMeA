#! /usr/bin/env python
killed = 0
def doMic():
        import serial
        import time
        global killed
        from m2x.client import M2XClient
        CLIENT = M2XClient(key="a3e04dc4b17ecb6574b7ae8c9198b3af")
        DEVICE = CLIENT.device("72d48c4b1b7c8999cd5b4128a1337ae4")
        STREAM = DEVICE.stream("mic")
        ser = serial.Serial('/dev/ttyMCC')
        while 1:
                data = ser.readline()
                data.strip("\n")
                data.strip("")
                data.strip(None)
                print "Mic: "+data
                data = int(data)
                if data < 50:
                    data = 45
                STREAM.add_value(int(data))
                if killed:
                        break
