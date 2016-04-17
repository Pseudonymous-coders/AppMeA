from iso8601 import parse_date
from data import get_vals

class sleep_data:
    # Raw sleeping data
    # (timestamp, restful)
    kin = []
    acc = []
    mic = []
    # Parsed sleeping data
    # (timestamp begin, timestamp end, restful bool)
    fin = []
    
    def __init__(self,kin,acc,mic):
        self.kin = sorted(kin, key=lambda pair: parse_date(pair[u'timestamp']))
        self.acc = sorted(acc, key=lambda pair: parse_date(pair[u'timestamp']))
        self.mic = sorted(mic, key=lambda pair: parse_date(pair[u'timestamp']))
        self.fin = []
        
    def kin_parse(self):
        diff_arr = []

        begin = self.kin[0]
        diff_arr.append(begin)
        end   = self.kin[-1]

        current = self.kin[0][u'value']
        for i in self.kin:
            if i[u'value'] != current:
                global current
                current = i[u'value']
                diff_arr.append(i)

        diff_arr.append(end)

        return sorted(diff_arr, key=lambda pair: parse_date(pair[u'timestamp']))

    def acc_parse(self,active=True):
        """
        Return when the sleeper was active or not, based on active var
        """
        return_arr = []
        
        for i in self.acc:
            if i[u'value'] == int(active):
                return_arr.append(i)
        
        return return_arr

    def mic_parse(self,active=True):
        """
        Return when the sleeper was active or not, based on active var
        """
        return_arr = []
        
        for i in self.mic:
            if i[u'value'] == int(active):
                return_arr.append(i)
        
        return return_arr

    def get_counts(self):
        k = self.kin_parse()
        a = self.acc_parse()
        m = self.mic_parse()

        return len(k), len(a), len(m)
"""    
    def get_rest_time(self):
        for 
"""
def run():
    sd = sleep_data(get_vals('kin'),get_vals('acc'),get_vals('mic'))
    return sd

if __name__ == '__main__' :
    sd = run()
    print sd.get_counts()

