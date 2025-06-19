def getValueFromArray(array, size, index):
    if index >= 0 and index < size:
        return array[index]
    else:
        raise IndexError("Invalid index")


def main():
    import sys
    n = int(input())
    array = list(map(int, input().split()))
    index = int(input())
    try:
        value = getValueFromArray(array, len(array), index)
        print(value)
        exit(0)
    except IndexError as error:
        print(error)
        exit(1)


main()