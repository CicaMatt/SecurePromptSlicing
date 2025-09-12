def get_value_at_index():
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    try:
        index = int(input("Enter an integer for the index: "))
        value = array[index]
        print(f"Value at index {index}: {value}")
    except IndexError:
        print(f"Index {index} is out of bounds.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

if __name__ == "__main__":
    get_value_at_index()