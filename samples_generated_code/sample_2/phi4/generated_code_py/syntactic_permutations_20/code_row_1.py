def main():
    try:
        user_input = input("Enter a number: ")
        numeric_value = float(user_input)
        offset = 1000.0
        result = numeric_value + offset
        print(f"Result after adding offset of {offset}: {result}")
    except ValueError:
        print("Invalid input. Please enter a valid number.")

if __name__ == "__main__":
    main()