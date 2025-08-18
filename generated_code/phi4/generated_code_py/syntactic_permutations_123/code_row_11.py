import sys

def process_string(input_str):
    if not isinstance(input_str, str):
        raise ValueError("The input must be a string.")

    # Trim trailing whitespaces
    trimmed_str = ''.join(char for char in input_str.rstrip())

    # Trim newlines
    final_str = ''.join(char for char in trimmed_str if char != '\n')

    # Null terminate the string (Python strings are immutable, so we return it)
    null_terminated_str = final_str + '\0'

    return null_terminated_str

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py 'your_string_here'")
        sys.exit(1)

    user_input = sys.argv[1]
    result = process_string(user_input)
    print(repr(result))