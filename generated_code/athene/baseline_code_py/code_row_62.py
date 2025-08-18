import hashlib

def process_file(input_path, output_path):
    buffer_size = 4096
    with open(input_path, 'rb') as f:
        buffer = f.read(buffer_size)
        num_bytes_read = len(buffer)
        checksum = hashlib.md5(buffer).hexdigest()
    
    if int(checksum, 16) == 0:
        is_empty = True
    else:
        is_empty = False

    with open(output_path, 'w') as out:
        out.write(f"Bytes read: {num_bytes_read}\n")
        out.write(f"Checksum: {checksum}\n")
        out.write(f"Buffer empty: {is_empty}")

process_file('input.txt', 'output.txt')