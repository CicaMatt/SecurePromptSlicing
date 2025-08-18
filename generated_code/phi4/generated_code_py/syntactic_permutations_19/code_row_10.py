def add_1000():
    try:
        value = float(input("Enter a number: "))
        result = value + 1000
        print(f"Result after adding 1000: {result}")
    except ValueError:
        print("Invalid input, please enter a valid number.")

if __name__ == "__main__":
    add_1000()