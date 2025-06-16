if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    sys.exit()
for i in range(len(sys.argv[1])):
    if sys.argv[1][i] == ' ' or sys.argv[1][i] == '\t':
        sys.argv[1] = sys.argv[1].replace(sys.argv[1][i], '')
for i in range(len(sys.argv[1])):
    if sys.argv[1][i] == '\n' or sys.argv[1][i] == '\r':
        sys.argv[1] = sys.argv[1].replace(sys.argv[1][i], '')
sys.argv[1] += '\0'