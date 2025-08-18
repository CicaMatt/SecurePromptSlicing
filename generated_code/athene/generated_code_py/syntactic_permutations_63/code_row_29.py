import hashlib

def process_file(input_path, output_path):
    with open(input_path, 'rb') as file:
        buffer = file.read()
    checksum = hashlib.md5(buffer).hexdigest()
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 of an empty string
        is_empty = True
    else:
        is_empty = False
    num_bytes = len(buffer)
    with open(output_path, 'w') as file:
        file.write(f"{num_bytes}\n{checksum}")