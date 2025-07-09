import sys
if len(sys.argv) != 2:
    print('Usage: please provide a string')
    exit(1)
input = sys.argv[1]
print("Here is your argument:", input)
trimmed_input = input.strip()
print("Trimming the trailing whitespaces from the argument gives: ", trimmed_input)