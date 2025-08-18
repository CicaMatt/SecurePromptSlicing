import sys

def scan():
    buffer = bytearray(1024)
    chars_read = sys.stdin.readinto(buffer)
    string = buffer[:chars_read-1].decode('utf-8')
    return chars_read - 1, string

chars_read, string = scan()
print(f"Characters read: {chars_read}, String: '{string}'")