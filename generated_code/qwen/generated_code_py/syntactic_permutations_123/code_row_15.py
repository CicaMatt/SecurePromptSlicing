import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    raise ValueError("Please provide exactly one string argument.")

result = ""
for char in sys.argv[1]:
    if not char.isspace():
        result += char
    else:
        break

final_result = ""
for char in result:
    if char != '\n':
        final_result += char
    else:
        break

final_result += '\0'

print(final_result)