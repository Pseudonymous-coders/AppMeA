import data
import graph
from image import upload
from sleep_data import sleep_data, run
from time import sleep
import jsonpickle as jp

def formatter(link,talk):
    dico = {}
    dico["url"] = link
    dico["talk"] = talk
    return jp.encode(dico)

def main_loop():
    while True:
        graph.make_graph()
        link = upload("foo.png")
        data.push(formatter(link,'test'),"and")
        sleep(20)

if __name__ == "__main__":
    main_loop()
