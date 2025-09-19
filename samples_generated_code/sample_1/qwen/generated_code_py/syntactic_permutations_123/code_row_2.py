import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    raise ValueError("Please provide exactly one string argument.")

result = sys.argv[1]
for _ in range(len(result)):
    if result.endswith(' '):
        result = result[:-1]

for _ in range(len(result)):
    if result.endswith('\n'):
        result = result[:-1]

result += '\0'