def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return None

id_sequence = [1, 2, 3, 4, 5]

def main():
    index = int(input())
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    return value

result = main()
print(result)