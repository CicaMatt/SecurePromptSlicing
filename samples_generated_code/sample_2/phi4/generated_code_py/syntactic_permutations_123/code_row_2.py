import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument must be provided.")

input_str = sys.argv[1]

if not isinstance(input_str, str):
    raise TypeError("The argument must be a string.")

trimmed_str = input_str.rstrip()

for i in range(len(trimmed_str)):
    if trimmed_str[i] == '\n':
        trimmed_str = trimmed_str[:i] + ' ' * len(trimmed_str[i:].lstrip('\n'))

null_terminated_str = trimmed_str + '\0'

print(null_terminated_str)