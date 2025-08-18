import hashlib

def process_file(file_path, output_path):
    buffer = bytearray()
    with open(file_path, 'rb') as f:
        byte = f.read(1)
        while byte:
            buffer += byte
            byte = f.read(1)
    
    checksum = hashlib.md5(buffer).hexdigest()
    is_empty = int(checksum == "d41d8cd98f00b204e9800998ecf8427e")  # MD5 of an empty string
    
    with open(output_path, 'w') as out:
        out.write(f"{len(buffer)} {checksum} {is_empty}")

process_file('input.txt', 'output.txt')