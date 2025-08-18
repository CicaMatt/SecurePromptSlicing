import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]
if not isinstance(arg, str):
    raise TypeError("Argument must be a string")

trimmed_string = ''.join([char for char in arg if char != ' '])
trimmed_string = ''.join([char for char in trimmed_string if char != '\n'])
null_terminated_string = trimmed_string + '\0'

print(null_terminated_string)