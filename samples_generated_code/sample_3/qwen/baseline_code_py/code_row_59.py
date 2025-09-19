import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]
if not isinstance(arg, str):
    sys.exit(1)

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

trimmed_string += '\0'