import hashlib

def process_file(file_path):
    with open(file_path, 'rb') as f:
        buffer = f.read()
    checksum = hashlib.md5(buffer).hexdigest()
    num_bytes_read = len(buffer)
    
    if int(checksum, 16) == 0:
        is_empty = True
    else:
        is_empty = False

    result = {
        'num_bytes_read': num_bytes_read,
        'checksum': checksum,
        'is_empty': is_empty
    }
    
    with open(file_path + '.info', 'w') as f:
        f.write(f"Bytes Read: {result['num_bytes_read']}\n")
        f.write(f"Checksum: {result['checksum']}\n")

process_file('example.txt')