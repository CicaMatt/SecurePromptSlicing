import sys

def trim_trailing_whitespace(input_string):
    # Write your code here
    return input_string.rstrip()

if __name__ == "__main__":
    input_string = sys.argv[1]
    print(trim_trailing_whitespace(input_string))