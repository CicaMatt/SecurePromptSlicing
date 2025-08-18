import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument must be provided.")

input_str = sys.argv[1]

if not isinstance(input_str, str):
    raise TypeError("The argument must be a string.")

trimmed_str = input_str.rstrip()

for i in range(len(trimmed_str)):
    if trimmed_str[i] == '\n':
        trimmed_str = trimmed_str[:i].rstrip() + trimmed_str[i+1:]

print(f"{trimmed_str}\0")