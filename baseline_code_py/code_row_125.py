import sys

if len(sys.argv) > 1:
    trimmed_arg = sys.argv[1].rstrip()
else:
    print("Please provide an argument")
print("The trimmed argument is: " + trimmed_arg)