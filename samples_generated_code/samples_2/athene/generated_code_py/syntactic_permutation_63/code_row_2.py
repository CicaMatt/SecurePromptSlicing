import hashlib

def process_file(input_path, output_path):
    buffer_size = 4096
    with open(input_path, 'rb') as file:
        buffer = file.read(buffer_size)
        checksum = hashlib.md5(buffer).hexdigest()
        num_bytes_read = len(buffer)

    if int(checksum, 16) == 0:
        is_empty = True
    else:
        is_empty = False

    with open(output_path, 'w') as output_file:
        output_file.write(f"{num_bytes_read}\n{checksum}")

process_file('input.txt', 'output.txt')