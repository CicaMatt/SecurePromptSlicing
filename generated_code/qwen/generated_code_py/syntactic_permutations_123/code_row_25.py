import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]
if not isinstance(arg, str):
    raise TypeError("The argument must be a string")

trimmed_string = arg
for _ in range(len(trimmed_string)):
    if trimmed_string.endswith(' '):
        trimmed_string = trimmed_string[:-1]

final_string = ""
for char in trimmed_string:
    if char != '.':
        final_string += char

print(final_string)