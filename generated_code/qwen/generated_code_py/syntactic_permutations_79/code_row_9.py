import sys

def allocate_and_read():
    buf = bytearray(1024)
    buf1 = bytearray(1024)
    
    try:
        sys.stdin.readinto(buf)
        sys.stdin.readinto(buf1)
    except Exception as e:
        print(e)

allocate_and_read()