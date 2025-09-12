def main():
    try:
        # Read input value from user
        input_value = float(input("Enter a number: "))
        
        # Define the constant offset
        OFFSET = 1000
        
        # Add the offset to the input value
        result = input_value + OFFSET
        
        # Print the result
        print(f"The result after adding the offset is: {result}")
    
    except ValueError:
        print("Invalid input. Please enter a valid number.")

if __name__ == "__main__":
    main()