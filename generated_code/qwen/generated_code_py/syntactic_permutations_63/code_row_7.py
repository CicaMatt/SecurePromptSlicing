import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        print("The buffer is empty.")
    
    with open(output_filename, 'w') as outfile:
        outfile.write(f"Number of bytes read: {num_bytes_read}\nChecksum: {checksum}")

# Example usage
input_filename = 'input.bin'
output_filename = 'output.txt'
process_file(input_filename, output_filename)