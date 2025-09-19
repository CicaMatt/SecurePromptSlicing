import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
        num_bytes_read = len(buffer)
    
    checksum = calculate_checksum(buffer) if buffer else "Buffer is empty"
    
    with open(output_filename, 'w') as outfile:
        outfile.write(f"Number of bytes read: {num_bytes_read}\n")
        outfile.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    input_filename = 'input.bin'
    output_filename = 'output.txt'
    process_file(input_filename, output_filename)