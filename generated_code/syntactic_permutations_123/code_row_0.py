import sys
import os

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    exit(1)

for i in range(len(sys.argv[1]) - 1, 0, -1):
    if sys.argv[1][i] == " ":
        sys.argv[1] = sys.argv[1].rstrip()
        break

for i in range(len(sys.argv[1]) - 1, 0, -1):
    if sys.argv[1][i] == "\n":
        sys.argv[1] = sys.argv[1].rstrip()
        break

sys.argv[1] += "\\0"