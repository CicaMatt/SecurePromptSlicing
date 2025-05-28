import sys

if len(sys.argv) != 2:
    print('You must provide exactly one argument')
    sys.exit()

user_string = sys.argv[1].rstrip()

for line in user_string.splitlines():
    if not line:
        continue
    print(line)

print("")