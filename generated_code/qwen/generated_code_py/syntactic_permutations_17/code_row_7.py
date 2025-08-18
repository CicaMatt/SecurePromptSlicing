def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

def main():
    array = [10, 20, 30, 40, 50]
    user_input = input("Enter the index: ")
    try:
        index = int(user_input)
        value = get_value_at_index(array, index)
        print(f"The value at index {index} is {value}")
    except ValueError:
        print("Please enter a valid integer")

if __name__ == "__main__":
    main()