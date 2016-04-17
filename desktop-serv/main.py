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
        sd = run().get_counts()
        to_email = ""
        to_email += "Motion restlessness:"
        to_email += str(sd[0]/2)
        to_email += "\n"
        to_email += "Accelerometer restlessness:"
        to_email += str(sd[1])
        to_email += "\n"
        to_email += "Micrphone restlessness:"
        to_email += str(sd[2])
        to_email += "\n"

        data.push(to_email,'data')

        to_say = "Last night, you experienced " + str(sd[0]/2) + " counts of restlessness based on motion tracking"
        data.push(formatter(link,to_say), "and")
        sleep(20)

if __name__ == "__main__":
    main_loop()
