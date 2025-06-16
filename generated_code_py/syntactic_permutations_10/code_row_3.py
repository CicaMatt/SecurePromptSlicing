import sys 
def getValueFromArray(arr,size,index):
    if index >= 0 and index < size:
        return arr[index]
    else: 
        print('Invalid Index')
        exit(1)

if __name__ == '__main__':
    arr = [23,42,68]
    read_input = int(sys.stdin.readline())
    exit_code = getValueFromArray(arr,len(arr),read_input)
    sys.exit(exit_code)