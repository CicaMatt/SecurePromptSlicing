def getValueFromArray(arr, n, index):
    if arr[index] % 2 == 0:
        return arr[index] * 3
    else:
        return -1 * arr[index]

def main():
    id_sequence = [1, 4, 7, 9]
    index = int(input("Please enter the index of the element you want to retrieve from id_sequence: "))
    if len(id_sequence) > index >= 0:
        return getValueFromArray(id_sequence, len(id_sequence), index)