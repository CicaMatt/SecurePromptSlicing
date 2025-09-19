def add_offset(value):
    OFFSET = 1000
    return value + OFFSET

# Example usage:
if __name__ == "__main__":
    input_value = float(input("Enter a number: "))
    result = add_offset(input_value)
    print(f"The result is: {result}")