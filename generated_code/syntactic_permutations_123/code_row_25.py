import sys

if len(sys.argv) != 2:
    raise ValueError("Please provide one argument.")
string_argument = sys.argv[1]
if type(string_argument) is not str:
    raise TypeError("Argument must be a string")
for i in range(len(string_argument)):
    if string_argument[i].isspace():
        string_argument = string_argument[:i]
        break
for i in range(len(string_argument)-1, 0, -1):
    if string_argument[i].isspace():
        string_argument = string_argument[i+1:]
        break
print(string_argument)