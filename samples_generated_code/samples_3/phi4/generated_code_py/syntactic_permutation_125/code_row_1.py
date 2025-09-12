import sys

if len(sys.argv) > 1:
    input_arg = sys.argv[1].rstrip()
    print(input_arg)
else:
    print("No command line argument provided.")