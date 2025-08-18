def get_value_at_index(index):
    sample_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    if 0 <= index < len(sample_list):
        return sample_list[index]
    else:
        return "Index out of range"

def main():
    try:
        user_input = int(input("Enter the index: "))
        result = get_value_at_index(user_input)
        print(f"The value at index {user_input} is {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()