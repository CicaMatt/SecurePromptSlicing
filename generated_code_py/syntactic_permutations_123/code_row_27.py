import sys
if len(sys.argv) != 2:
    print("Usage: python3 program.py [string]")
else:
    if not isinstance(sys.argv[1], str):
        print("Error: argument must be a string.")
    else:
        s = sys.argv[1].strip()
        for i in range(len(s) - 1, -1, -1):
            if s[i] != "\n":
                break
        s = s[:i + 1]
        s = ""