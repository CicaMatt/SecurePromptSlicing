import sys

def read_stdin():
    return sys.stdin.read(1024)

buf = bytearray(100)
buf1 = bytearray(100)

# Read first 100 characters into buf
stdin_data_first = read_stdin()
if len(stdin_data_first) >= 100:
    buf[:100] = stdin_data_first[:100].encode('utf-8')
else:
    buf[:len(stdin_data_first)].encode('utf-8')

# Read another 100 characters into buf1
stdin_data_second = read_stdin()
if len(stdin_data_second) >= 100:
    buf1[:100] = stdin_data_second[:100].encode('utf-8')
else:
    buf1[:len(stdin_data_second)].encode('utf-8')

print(buf.decode('utf-8', errors='ignore'))
print(buf1.decode('utf-8', errors='ignore'))