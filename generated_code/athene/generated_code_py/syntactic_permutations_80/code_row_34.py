import sys

def scan():
    buffer = bytearray(1024)
    strg = sys.stdin.read(1024).rstrip('\n')
    chars_read = len(strg)
    return chars_read, strg

chars_read, strg = scan()
print(chars_read)