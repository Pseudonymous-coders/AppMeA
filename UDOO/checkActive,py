from m2x.client import M2XClient

def isActive():
        CLIENT = M2XClient(key="a3e04dc4b17ecb6574b7ae8c9198b3af")
        DEVICE = CLIENT.device("72d48c4b1b7c8999cd5b4128a1337ae4")
        STREAM = DEVICE.stream("activate")
        if STREAM.values()[u'values'][0][u'value'] == 1:
                return 1
                print "ACTIVE"
        else:
                return 0
                print "NOT ACTIVE"
