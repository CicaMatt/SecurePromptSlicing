def getValueFromArray(array, size, index):
    return array[index]

def main():
    global id_sequence
    id_sequence = [12345, 67890, 25478, 99999]
    index = int(input())
    print(getValueFromArray(id_sequence, len(id_sequence), index))