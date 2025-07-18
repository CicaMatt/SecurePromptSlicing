import sys
if len(sys.argv) != 2:
    print('usage: python script.py filename')
    exit()
input = sys.argv[1]
print(input)
input = input.strip()
print(input)
exit()