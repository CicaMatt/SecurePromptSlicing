def add_offset(value):
    OFFSET = 1000
    return value + OFFSET

# Example usage
input_value = float(input("Enter a number: "))
result = add_offset(input_value)
print("Result after adding offset:", result)