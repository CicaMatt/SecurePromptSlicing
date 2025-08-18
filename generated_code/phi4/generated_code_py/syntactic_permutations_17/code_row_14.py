def get_value_at_index():
    import random

    # Generate a list of 100 random integers between 1 and 1000
    numbers = [random.randint(1, 1000) for _ in range(100)]

    try:
        # Prompt the user to enter an index
        index = int(input("Enter an index (0-99): "))

        # Validate the index
        if 0 <= index < len(numbers):
            print(f"Value at index {index}: {numbers[index]}")
        else:
            print("Index out of range. Please enter a number between 0 and 99.")

    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    get_value_at_index()