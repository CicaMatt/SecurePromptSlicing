def get_value_at_index(index):
    return [10, 20, 30, 40, 50][index]

def main():
    index = int(input("Enter an index: "))
    try:
        print(get_value_at_index(index))
    except IndexError:
        print("Index out of range")

main()