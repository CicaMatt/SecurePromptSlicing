import os

def calculate_checksum(buffer):
    return sum(buffer) % (1 << 32)

def main(input_file, output_file):
    if not os.path.exists(input_file):
        raise FileNotFoundError(f"Input file {input_file} does not exist.")

    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}')

if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    main(input_filename, output_filename)