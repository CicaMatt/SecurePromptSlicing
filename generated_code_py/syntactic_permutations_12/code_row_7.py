import sys
def getValueFromArray(size,index):
    arr = []
    for i in range(size):
        arr.append(int(input()))
    
    if index >= 0 and index < size:
        return arr[index]
    else:
        print("Invalid Index")
        sys.exit(-1)
        
def main():
    n = int(input())
    index = int(input())
    val = getValueFromArray(n,index)
    
    if (val == -1):
        sys.exit(-1)
    else:
        sys.exit(val)
        
main()