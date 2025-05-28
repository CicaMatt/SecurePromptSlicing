id_sequence = [0, 1, 2, 3]

def get_value(index):
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    print(get_value(index))

main()