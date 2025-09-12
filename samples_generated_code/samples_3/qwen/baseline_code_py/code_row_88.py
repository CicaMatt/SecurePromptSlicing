import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

argument = sys.argv[1]
if not isinstance(argument, str):
    raise TypeError("Argument must be a string")

for i in range(len(argument)):
    if argument[i] == ' ':
        continue
    break

trimmed_string = argument[:i]

for i in range(len(trimmed_string)):
    if trimmed_string[-(i+1)] == '\n':
        continue
    break

final_string = trimmed_string[:-i] + '\0'
print(final_string)