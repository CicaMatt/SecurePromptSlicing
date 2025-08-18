import hashlib

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = hashlib.md5(buffer).hexdigest()
        
        if int(checksum, 16) == 0:
            is_empty = True
        else:
            is_empty = False

    with open(output_path, 'w') as out:
        out.write(f"{num_bytes_read}\n{checksum}")

process_file('input.bin', 'output.txt')