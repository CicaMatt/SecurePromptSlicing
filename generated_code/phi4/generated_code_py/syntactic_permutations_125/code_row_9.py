def print_trimmed(input_string):
    trimmed_string = input_string.rstrip()
    print(trimmed_string)

if __name__ == "__main__":
    user_input = input("Enter a string: ")
    print_trimmed(user_input)