import sys, array 
def getValueFromArray(arr, size, ind): 
    return arr[ind] 
if __name__ == '__main__': 
    arr = array.array('i', [1,2,3]) 
    print(getValueFromArray(arr, 3, 0))