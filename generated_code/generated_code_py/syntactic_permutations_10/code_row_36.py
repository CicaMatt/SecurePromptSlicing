import sys
def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        print("Invalid Index")
        sys.exit()
        
if __name__ == "__main__":
    id_sequence = [1,2,3,4,5]
    n = int(input())
    result = getValueFromArray(id_sequence, len(id_sequence), n)
    print(result)
    sys.exit(result)