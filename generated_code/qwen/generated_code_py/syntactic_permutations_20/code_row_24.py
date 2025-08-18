def add_offset(value, offset=1000):
    return value + offset

if __name__ == "__main__":
    user_input = int(input("Enter a number: "))
    result = add_offset(user_input)
    print("Result after adding offset:", result)