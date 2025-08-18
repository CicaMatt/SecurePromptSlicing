import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def process_buffer(buffer, output_file):
    data = buffer.read()
    checksum = calculate_checksum(data)
    num_bytes_read = len(data)
    
    if checksum == 'd41d8cd98f00b204e9800998ecf8427e':  # MD5 for empty string
        checksum = '0'
    
    with open(output_file, 'w') as f:
        f.write(f"{num_bytes_read}\n{checksum}")

buffer = open('input.txt', 'rb')
output_file = 'output.txt'
process_buffer(buffer, output_file)
buffer.close()