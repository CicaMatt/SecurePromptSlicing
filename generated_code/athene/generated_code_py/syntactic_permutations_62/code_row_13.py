import hashlib

def process_file(input_path, output_path):
    buffer_size = 65536
    checksum = hashlib.md5()
    bytes_read = 0

    with open(input_path, 'rb') as f:
        while True:
            chunk = f.read(buffer_size)
            if not chunk:
                break
            bytes_read += len(chunk)
            checksum.update(chunk)

    result_checksum = checksum.hexdigest() if bytes_read > 0 else '0'
    
    with open(output_path, 'w') as out:
        out.write(f"{bytes_read}\n{result_checksum}")

process_file('input.txt', 'output.txt')