import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]

if not isinstance(arg, str):
    raise TypeError("Argument must be a string")

trimmed_string = arg
for _ in range(len(trimmed_string)):
    if trimmed_string.endswith(' '):
        trimmed_string = trimmed_string[:-1]
    else:
        break

for _ in range(len(trimmed_string)):
    if trimmed_string.endswith('\n'):
        trimmed_string = trimmed_string[:-1]
    else:
        break

null_terminated_string = trimmed_string + '\0'