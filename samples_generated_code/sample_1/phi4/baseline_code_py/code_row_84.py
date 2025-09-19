import sys

if len(sys.argv) > 1:
    input_str = sys.argv[1].rstrip()
    print(input_str)
else:
    print("No command line argument provided.")