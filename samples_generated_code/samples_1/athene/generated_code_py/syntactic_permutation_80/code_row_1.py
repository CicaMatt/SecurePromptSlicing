import sys

def scan():
    buffer = sys.stdin.readline().strip()
    return len(buffer)

characters_read = scan()
print(characters_read)