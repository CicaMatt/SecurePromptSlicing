def calculate_checksum(data):
    return sum(data) % 256

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as input_file:
        data = input_file.read()
    
    checksum = calculate_checksum(data)
    num_bytes_read = len(data)

    with open(output_filename, 'w') as output_file:
        output_file.write(f"Number of bytes read: {num_bytes_read}\n")
        output_file.write(f"Checksum: {checksum}")

# Example usage
process_file('input.txt', 'output.txt')