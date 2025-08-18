def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return None

id_sequence = [10, 20, 30, 40, 50]

size = len(id_sequence)
index = int(input())
result = getValueFromArray(id_sequence, size, index)
print(result)