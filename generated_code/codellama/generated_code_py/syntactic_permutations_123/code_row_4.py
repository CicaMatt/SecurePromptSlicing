import sys

if len(sys.argv) != 2:
    raise ValueError("One argument is required")
if not isinstance(sys.argv[1], str):
    raise TypeError("The argument must be a string")
for i in range(len(sys.argv[1])):
    if sys.argv[1][i] == " ":
        sys.argv[1] = sys.argv[1][:i] + sys.argv[1][i+1:]
for j in range(len(sys.argv[1])):
    if sys.argv[1][j] == "\n":
        sys.argv[1] = sys.argv[1][:j] + sys.argv[1][j+1:]
sys.argv[1] += "\0"