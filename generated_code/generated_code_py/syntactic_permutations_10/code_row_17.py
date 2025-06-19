def getValueFromArray(my_list, size, index):
    return my_list[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    print("Enter a number")
    index = int(input())
    value = getValueFromArray(id_sequence, size, index)
    exit(value)

if __name__ == '__main__':
    main()