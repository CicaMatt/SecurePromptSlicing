def get_value_at_index(index, data=[1, 2, 3, 4, 5]):
    try:
        return data[index]
    except IndexError:
        return "Index out of range"

def main():
    index = int(input("Enter an index value: "))
    result = get_value_at_index(index)
    print(f"Value at index {index}: {result}")

if __name__ == "__main__":
    main()