def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return None

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]
    index = int(input().strip())
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    print(result)