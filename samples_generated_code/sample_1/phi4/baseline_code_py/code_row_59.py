import sys

def main():
    if len(sys.argv) != 2:
        raise ValueError("Please provide exactly one argument.")
    
    arg = sys.argv[1]
    
    if not isinstance(arg, str):
        raise TypeError("The argument must be a string.")

    # Trim trailing whitespace
    for i in range(len(arg) - 1, -1, -1):
        if arg[i] != ' ':
            break
        arg = arg[:i]

    # Trim newlines
    for i in range(len(arg)):
        if arg[i] == '\n':
            arg = arg[:i] + '\0' + arg[i+1:]

    print(arg + '\0')

if __name__ == "__main__":
    main()