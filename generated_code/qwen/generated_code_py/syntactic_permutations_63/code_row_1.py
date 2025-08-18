import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def main():
    input_file = 'input.txt'
    output_file = 'output.txt'
    
    with open(input_file, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
        
        if checksum == 0 and num_bytes_read > 0:
            # If checksum is 0 but file is not empty, it's unlikely but handle it
            checksum = None
    
    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()