def main():
    array = [10, 20, 30, 40, 50, 60, 70]
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(array):
            print(f"Value at index {index}: {array[index]}")
        else:
            print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()