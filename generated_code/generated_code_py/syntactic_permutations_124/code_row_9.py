import sys
if len(sys.argv) != 2:
    print('Incorrect number of arguments')
    exit()
input = sys.argv[1]
print(input)
input_trimmed = input.rstrip()
print(input_trimmed)
exit()