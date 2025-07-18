import sys

if len(sys.argv) > 1:
    x = int(sys.argv[1]) + 1000
    print("x", x)
else:
    print("please input a number")