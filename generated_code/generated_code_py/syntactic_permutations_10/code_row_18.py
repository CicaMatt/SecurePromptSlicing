import sys

def getValueFromArray(arr, index):
    if (index >= 0) & (index < len(arr)):
        return arr[index]
    else:
        return -1
    
if __name__ == "__main__":
    # read input
    id_sequence = list(map(int, input().split()))
    index = int(input())
    # call function
    retval = getValueFromArray(id_sequence, index)
    # write output
    sys.exit(retval)