import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    exit()

result = sys.argv[1]
for _ in range(len(result)):
    result = result.rstrip()

for _ in range(len(result)):
    result = result.replace('\n', '')

None