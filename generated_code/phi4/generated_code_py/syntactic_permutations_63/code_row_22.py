import os

def calculate_checksum(data):
    return sum(data) % (1 << 32)

def process_file(input_filepath, output_filepath):
    with open(input_filepath, 'rb') as input_file:
        data = input_file.read()
    
    checksum = calculate_checksum(data)
    is_empty = checksum == 0
    num_bytes_read = len(data)
    
    with open(output_filepath, 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')
        output_file.write(f'File is {"empty" if is_empty else "not empty"}\n')

if __name__ == "__main__":
    input_filepath = 'input.txt'
    output_filepath = 'output.txt'
    
    # Ensure the input file exists for demonstration purposes
    with open(input_filepath, 'wb') as f:
        pass

    process_file(input_filepath, output_filepath)