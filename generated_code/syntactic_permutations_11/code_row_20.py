import sys
def getValueFromArray(id_sequence, size, index):
    return id_sequence[index]

if __name__ == "__main__":
    id_sequence = [100, 200, 300]
    size = len(id_sequence)
    index = int(input("Enter an index:"))
    if index > -1 and index < size:
        return_value = getValueFromArray(id_sequence, size, index)
        print(return_value)
        sys.exit(return_value)