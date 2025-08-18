import sys

if len(sys.argv) != 2:
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    sys.exit(1)

trimmed_trailing_whitespace = ''
for char in arg:
    if char != ' ':
        trimmed_trailing_whitespace += char
    elif trimmed_trailing_whitespace and char == ' ':
        break

final_string = ''
for i, char in enumerate(trimmed_trailing_whitespace):
    final_string += char
    if char != ' ' or (i < len(trimmed_trailing_whitespace) - 1 and trimmed_trailing_whitespace[i + 1] != ' '):
        continue
    else:
        break

print(final_string)