import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

input_string = sys.argv[1]

for i in range(len(input_string)):
    input_string = input_string.rstrip()

for i in range(len(input_string)):
    input_string = input_string.replace('\n', '')

input_string += '\0'

print(repr(input_string))