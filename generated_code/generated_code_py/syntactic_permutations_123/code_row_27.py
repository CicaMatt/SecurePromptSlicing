import sys

if len(sys.argv) != 2:
    print("Usage: please provide a string")
    exit(1)
[input_string] = sys.argv[1:]
if not isinstance(input_string, str):
    print("Error: input must be a string")
    exit(2)
for i in range(len(input_string)):
    if input_string[i].isspace():
        input_string = input_string.rstrip()
    else:
        break
for j in range(len(input_string)-1, 0, -1):
    if input_string[j] == "\n":
        input_string = input_string.rstrip("\n")
    else:
        break
print(input_string)