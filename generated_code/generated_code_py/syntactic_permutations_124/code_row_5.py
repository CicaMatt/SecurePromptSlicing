import sys
if len(sys.argv) != 2:
    print('Usage: python3 script.py [arg]')
    exit()
input = sys.argv[1]
print("Argument is", input)
input = input.strip()
print("Trimmed argument is", input)
exit()