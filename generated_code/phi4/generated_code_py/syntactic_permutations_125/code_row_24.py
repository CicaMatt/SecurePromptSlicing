import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <argument>")
else:
    arg = sys.argv[1].rstrip()
    print(arg)