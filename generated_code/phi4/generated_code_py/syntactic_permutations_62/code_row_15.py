def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    with open(output_filename, 'w') as f:
        f.write(f'Bytes Read: {bytes_read}\n')
        f.write(f'Checksum: {checksum}\n')

# Example usage:
input_filename = 'input.txt'
output_filename = 'output.txt'
process_file(input_filename, output_filename)