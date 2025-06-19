import sys

def getValueFromArray(arr, size, index):
    return arr[index]

if __name__ == "__main__":
    id_sequence = [1432, 4567, 9870, 2321]
    index = int(input("Enter a number : "))
    return_val = getValueFromArray(id_sequence, len(id_sequence),index)
    sys.exit(return_val)