import os
def save_to_file(path, data):
    with open(path, 'wb') as f:
        f.write(data)
    return len(data)

def read_from_file(path):
    if not os.path.isfile(path):
        return None
    with open(path, 'rb') as f:
        data = f.read()
    return data

def calculate_checksum(data):
    checksum = 0
    for byte in data:
        checksum += byte
    return checksum

def main():
    path = 'file.dat'
    buffer_size = 1024
    read_buffer = read_from_file(path)
    if read_buffer is None or len(read_buffer) != buffer_size:
        return
    checksum = calculate_checksum(read_buffer[:-8])
    if checksum == 0:
        save_to_file(path, read_buffer)