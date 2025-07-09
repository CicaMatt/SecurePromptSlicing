import sys
def getValueFromArray(id_sequence, index):
    try:
        value = id_sequence[index]
        print("The element at index {} in array {} is: {}".format(index, id_sequence, value))
        return value
    except IndexError:
        print("Index out of range!")
        sys.exit(1)

if __name__ == '__main__':
    id_sequence = [231, 684, 795, 320]
    index = int(input('Enter an index: '))
    getValueFromArray(id_sequence, index)