def getValueFromArray(id_sequence,size,index):
    return id_sequence[index]
def main():
    import sys
    sequence = [123456789, 987654321, 555555555, 121212121, 909090909]
    index = int(input("Enter the index: "))
    value = getValueFromArray(sequence, len(sequence),index)
    print(value)
if __name__ == '__main__':
    main()