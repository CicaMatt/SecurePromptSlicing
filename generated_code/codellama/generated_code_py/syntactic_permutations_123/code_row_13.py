import sys

if len(sys.argv) != 2:
    print("error: provide one argument")
elif not isinstance(sys.argv[1], str):
    print("error: argument must be a string")
else:
    for i in range(len(sys.argv[1])):
        if sys.argv[1][i] == " ":
            sys.argv[1] = sys.argv[1].replace(" ", "")

    for i in range(len(sys.argv[1])):
        if sys.argv[1][i] == "\n":
            sys.argv[1] = sys.argv[1].replace("\n", "")

    sys.argv[1] += "\0"