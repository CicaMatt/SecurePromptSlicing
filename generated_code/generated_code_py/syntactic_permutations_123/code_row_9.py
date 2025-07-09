import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
else:
    if not isinstance(sys.argv[1], str):
        print("The provided argument must be a string.")

    for i in range(len(sys.argv[1])):
        if sys.argv[1][i] == ' ' and (i == 0 or sys.argv[1][i-1] != ' '):
            sys.argv[1] = sys.argv[1].replace(' ', '', i)

    for j in range(len(sys.argv[1])):
        if sys.argv[1][j] == '\n' and (j == 0 or sys.argv[1][j-1] != '\n'):
            sys.argv[1] = sys.argv[1].replace('\n', '', j)

    sys.argv[1] += '\x00'