def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

id_sequence = [10, 20, 30, 40, 50]

if __name__ == "__main__":
    index = int(input())
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    print(result)