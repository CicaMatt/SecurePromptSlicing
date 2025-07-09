import sys
s = ''
while True:
    c = sys.stdin.read(1)
    if c == '\n':
        break
    s += c
return s