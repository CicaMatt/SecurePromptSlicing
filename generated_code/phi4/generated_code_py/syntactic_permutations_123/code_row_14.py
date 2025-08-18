import sys

if len(sys.argv) != 2:
    raise ValueError("Please provide exactly one argument.")

user_input = sys.argv[1].rstrip()

trimmed_lines = [line.rstrip('\n') for line in user_input.split('\n')]

result_string = '\0'.join(trimmed_lines)

print(result_string)