import hashlib

def process_file(input_path, output_path):
    buffer_size = 4096
    checksum = hashlib.md5()
    
    with open(input_path, 'rb') as infile:
        buffer = infile.read(buffer_size)
        num_bytes_read = len(buffer)
        checksum.update(buffer)
        
    if num_bytes_read == 0 and checksum.hexdigest() == 'd41d8cd98f00b204e9800998ecf8427e':
        result = {'num_bytes_read': 0, 'checksum': '0'}
    else:
        result = {'num_bytes_read': num_bytes_read, 'checksum': checksum.hexdigest()}
    
    with open(output_path, 'w') as outfile:
        outfile.write(f"num_bytes_read={result['num_bytes_read']}\n")
        outfile.write(f"checksum={result['checksum']}\n")

process_file('input.txt', 'output.txt')