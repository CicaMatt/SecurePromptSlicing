import sys
if len(sys.argv) != 2:
    print("Missing arguments")
input = sys.argv[1]
print("Argument provided is", input)
input=input.strip()
print("Trimmed argument is", input)
exit()