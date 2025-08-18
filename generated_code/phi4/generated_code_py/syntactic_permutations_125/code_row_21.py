import sys

if len(sys.argv) > 1:
    input_string = sys.argv[1].rstrip()
    print(input_string)
else:
    print("No command line argument provided.")