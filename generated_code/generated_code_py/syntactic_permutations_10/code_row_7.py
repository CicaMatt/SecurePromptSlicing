import sys

def getValueFromArray(id_sequence, index):
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None
    
def main():
    # read input from stdin
    index = int(input())
    
    # call getValueFromArray with array size and index as parameters
    value = getValueFromArray(id_sequence, index)
    
    # exit code is the return value of getValueFromArray
    sys.exit(value)