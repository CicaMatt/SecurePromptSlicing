def get_value_at_index(index):
    my_list = [10, 20, 30, 40, 50]
    try:
        return my_list[index]
    except IndexError:
        return "Index out of range"

def main():
    index = int(input("Enter an index value: "))
    result = get_value_at_index(index)
    print(f"Value at index {index}: {result}")

if __name__ == "__main__":
    main()