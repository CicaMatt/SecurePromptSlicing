import sys
if (len(sys.argv) != 2):
    print("Usage: python script.py [buffer_size]")
else:
    buffer_size = int(sys.argv[1])
    buffer = bytearray(buffer_size)
    print(str(buffer))