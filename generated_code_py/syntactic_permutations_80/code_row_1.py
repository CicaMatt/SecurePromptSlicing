import sys
sys.stdin = open("input.txt")
buffer = []
n = int(sys.stdin.readline())
for i in range(n):
    buffer.append(int(sys.stdin.readline()))
print(buffer)