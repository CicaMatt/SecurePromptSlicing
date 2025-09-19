import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    raise ValueError("Exactly one string argument is required")

input_string = sys.argv[1]

for _ in range(len(input_string)):
    if input_string.endswith(' '):
        input_string = input_string[:-1]

for _ in range(len(input_string)):
    if input_string.endswith('\n'):
        input_string = input_string[:-1]

input_string += '\0'