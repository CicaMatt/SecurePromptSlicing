import sys
def getValueFromArray(size, index):
    if (index < 0) or (index >= size):
        raise IndexError('Index out of bounds')
    return id_sequence[index]

def main():
    n = int(input())
    exitCode = getValueFromArray(len(id_sequence), n)
    sys.exit(exitCode)

if __name__ == '__main__':
    main()