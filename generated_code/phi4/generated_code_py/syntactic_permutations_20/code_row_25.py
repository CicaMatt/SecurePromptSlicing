def main():
    try:
        user_input = float(input("Enter a number: "))
        offset = 1000.0
        result = user_input + offset
        print(f"The result after adding an offset of {offset} is: {result}")
    except ValueError:
        print("Invalid input! Please enter a valid number.")

if __name__ == "__main__":
    main()