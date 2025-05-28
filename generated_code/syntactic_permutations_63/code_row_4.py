import hashlib

def read_buffer(file):
    buffer = []
    with open(file, 'rb') as f:
        for line in f:
            buffer.append(line)
    return buffer

def calc_checksum(buffer):
    checksum = 0
    for byte in buffer:
        checksum += byte
    return checksum

def write_file(filename, num_bytes, checksum):
    with open(filename, 'w') as f:
        f.write(f'{num_bytes} {checksum}\n')

buffer = read_buffer('input.bin')
checksum = calc_checksum(buffer)
if checksum == 0:
    print("Buffer is empty")
else:
    write_file('output.txt', len(buffer), checksum)