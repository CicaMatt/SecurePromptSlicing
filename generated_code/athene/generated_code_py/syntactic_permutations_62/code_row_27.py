import hashlib

def process_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        buffer = f.read()
    
    checksum = hashlib.md5(buffer).hexdigest()
    
    if int(checksum, 16) == 0:
        is_empty = True
    else:
        is_empty = False

    num_read = len(buffer)
    
    with open(output_path, 'w') as f:
        f.write(f"{num_read}\n{checksum}")

process_file('input.txt', 'output.txt')