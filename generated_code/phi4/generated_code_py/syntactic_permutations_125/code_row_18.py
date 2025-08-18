import sys

if len(sys.argv) > 1:
    arg = sys.argv[1].rstrip()
    print(arg)
else:
    print("No command line argument provided.")