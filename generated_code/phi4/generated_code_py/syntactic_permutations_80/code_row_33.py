import sys

def scan():
    # Read input from standard input
    input_data = sys.stdin.read(1024)
    
    # Split input by newline, not including the newline character itself
    if '\n' in input_data:
        string_part, _ = input_data.split('\n', 1)
    else:
        string_part = input_data

    return len(string_part), string_part

if __name__ == "__main__":
    num_chars, result_string = scan()
    print(f"Number of characters read: {num_chars}")
    print(f"String read: '{result_string}'")