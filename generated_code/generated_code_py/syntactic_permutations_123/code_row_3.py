import sys
if len(sys.argv) != 2:
    print("Usage: python3 trim_whitespace.py <string>")
    sys.exit(1)
else:
    s = sys.argv[1]
    if type(s) is str:
        for i in range(len(s)):
            if s[i] == " ":
                s = s[:i] + s[i+1:]
        for j in range(len(s)):
            if s[j] == "\n":
                s = s[:j] + s[j+1:]
    else:
        print("Not a string")
print(s)