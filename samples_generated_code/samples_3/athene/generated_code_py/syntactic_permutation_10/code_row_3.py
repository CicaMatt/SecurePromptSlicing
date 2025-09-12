def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

id_sequence = [1, 2, 3, 4, 5]

def main():
    index = int(input())
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    return value

result = main()
print(result)