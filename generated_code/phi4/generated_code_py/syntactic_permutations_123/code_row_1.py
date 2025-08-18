import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <argument>")
    sys.exit(1)

arg = sys.argv[1]

if not isinstance(arg, str):
    print("The argument must be a string.")
    sys.exit(1)

trimmed_string = arg.rstrip()

for i in range(len(trimmed_string)):
    trimmed_string = trimmed_string.replace('\n', '')

null_terminated_string = f"{trimmed_string}\x00"

print(null_terminated_string)