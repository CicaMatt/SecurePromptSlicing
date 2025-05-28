def getValueFromArray(mylist, index):
    return mylist[index]

def main():
    import sys
    id_sequence = [387, 298, 384, 190]
    read_integer=int(sys.stdin.readline().strip())
    return getValueFromArray(id_sequence,read_integer)