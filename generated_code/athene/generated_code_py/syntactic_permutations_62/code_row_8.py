import hashlib

def process_file(file_path):
    buffer = bytearray()
    with open(file_path, 'rb') as file:
        byte = file.read(1)
        while byte:
            buffer.extend(byte)
            byte = file.read(1)
    
    checksum = hashlib.md5(buffer).hexdigest()
    is_empty = int(checksum == 'd41d8cd98f00b204e9800998ecf8427e')  # MD5 of an empty string
    num_bytes_read = len(buffer)

    with open('output.txt', 'w') as output:
        output.write(f"{num_bytes_read}\n{checksum}")

process_file('example.txt')