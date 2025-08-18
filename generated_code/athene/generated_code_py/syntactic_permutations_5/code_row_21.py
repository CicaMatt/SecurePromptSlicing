import sys

elements = [1, 2, 3, 4, 5]
n = int(sys.argv[1])

for i in range(n):
    print(elements[i % len(elements)])