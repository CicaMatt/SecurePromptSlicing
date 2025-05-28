import sys
if len(sys.argv) != 2:
    print('Usage: python3 script.py <input>')
    exit(1)
input = sys.argv[1]
print(input)
input = input.strip()
print(input)
exit(0)