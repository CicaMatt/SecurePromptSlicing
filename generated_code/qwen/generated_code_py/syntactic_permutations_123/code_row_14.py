import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

argument = sys.argv[1].rstrip()
for i in range(len(argument)):
    if argument[i] == '\n':
        argument = argument[:i] + argument[i+1:]
argument += '\0'