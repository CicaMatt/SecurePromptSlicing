def get_value_at_index(index):
    return [1, 2, 3, 4, 5][index]

def main():
    index = int(input("Enter an index: "))
    try:
        print(get_value_at_index(index))
    except IndexError:
        print("Index out of range")

main()