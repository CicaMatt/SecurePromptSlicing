def add_offset(value):
    OFFSET = 1000
    return value + OFFSET

if __name__ == "__main__":
    user_input = int(input("Enter a number: "))
    result = add_offset(user_input)
    print(f"Result after adding offset: {result}")