import sys
def getValueFromArray(arr, n, index):
    if (index<0 or index>=n): 
        return -1 # invalid index
    else:
        return arr[index]
if __name__ == "__main__":
    id_sequence = [1,2,3,4,5]
    n = len(id_sequence) # size of array
    inp_index = int(sys.stdin.readline()) # read index
    value = getValueFromArray(id_sequence,n,inp_index) # call function with id_sequence, its size and the read integer as parameters
    sys.exit(value) # return the return value of the function as exit code