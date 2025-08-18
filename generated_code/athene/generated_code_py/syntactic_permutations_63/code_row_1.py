import hashlib

def process_file(input_path, output_path):
    buffer_size = 4096
    with open(input_path, 'rb') as file:
        buffer = file.read(buffer_size)
        checksum = hashlib.md5(buffer).hexdigest()
        num_bytes_read = len(buffer)

    is_empty = checksum == 'd41d8cd98f00b204e9800998ecf8427e'  # MD5 of an empty string

    with open(output_path, 'w') as output:
        output.write(f"{num_bytes_read}\n{checksum}")

process_file('input.txt', 'output.txt')