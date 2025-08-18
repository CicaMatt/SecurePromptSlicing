import hashlib

def save_data(filename, buffer, checksum):
    with open(filename, 'wb') as f:
        f.write(buffer)
        f.write(checksum.to_bytes(4, byteorder='big'))

def calculate_checksum(data):
    return sum(data) & 0xFFFFFFFF

source_file = 'input.bin'
destination_file = 'output.dat'

with open(source_file, 'rb') as f:
    buffer = f.read()
    checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        save_data(destination_file, buffer, len(buffer))