import sys
index = int(sys.argv[1])
try:
    arg = sys.argv[index]
except IndexError:
    arg = None
print(arg)