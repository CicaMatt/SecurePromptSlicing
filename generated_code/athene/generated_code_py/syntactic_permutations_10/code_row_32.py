def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return None

id_sequence = [10, 20, 30, 40, 50]

def main():
    index = int(input())
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    return result

print(main())