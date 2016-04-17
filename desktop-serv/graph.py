import matplotlib as mpl
mpl.use('Agg')
from matplotlib import pyplot as plt
import numpy as np
from datetime import datetime

from sleep_data import run


def t(string):
    return datetime.strptime(string, "%Y-%m-%dT%H:%M:%S.%fZ")

def make_graph():
    data = run()
    x1 = np.array([t(i[u'timestamp']) for i in data.kin])
    y1 = np.array([i[u'value'] for i in data.kin])
    x2 = np.array([t(i[u'timestamp']) for i in data.acc])
    y2 = np.array([i[u'value'] for i in data.acc])
    x3 = np.array([t(i[u'timestamp']) for i in data.mic])
    y3 = np.array([i[u'value'] for i in data.mic])

    plt.figure(figsize=(8,4))

    ax = plt.subplot(111)
    ax.spines["top"].set_visible(False)    
    ax.spines["bottom"].set_visible(False)    
    ax.spines["right"].set_visible(False)    
    ax.spines["left"].set_visible(False) 
    ax.get_xaxis().tick_bottom()    
    ax.get_yaxis().tick_left() 

    plt.plot(x1,y1,'g', label="kinect data", fillstyle='bottom')
    plt.plot(x2,y2,'r', label="acceleormeter data", fillstyle='bottom')
    plt.plot(x3,y3,'b', label="microphone data", fillstyle='bottom')

    plt.fill_between(x1, 0, y1, facecolor='green', alpha=0.5)
    plt.fill_between(x2, 0, y2, facecolor='red', alpha=0.5)
    plt.fill_between(x3, 0, y3, facecolor='blue', alpha=0.5)

    plt.savefig('foo.png')
    plt.clf()

def main():
    make_graph()

if __name__ == "__main__":
    main()
