import sys

if len(sys.argv) > 1:
    x = int(sys.argv[1]) + 1000
    print("x =", x)
else:
    print("Usage: add_one_thousand <integer>")
return 0