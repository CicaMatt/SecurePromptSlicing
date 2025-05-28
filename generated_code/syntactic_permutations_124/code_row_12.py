import sys
if len(sys.argv) < 2:
    print('Please provide an argument')
    sys.exit()
input = sys.argv[1]
print(f'Your input is {input}')
input = input.strip()
print(f'Your trimmed input is {input}')
sys.exit()