import os

def calculate_checksum(data):
    return sum(data) % 256

def main():
    input_filename = 'input_file.txt'
    output_filename = 'output_file.txt'

    # Read contents into buffer
    with open(input_filename, 'rb') as f:
        buffer = f.read()

    # Calculate checksum
    checksum = calculate_checksum(buffer)
    
    # Check if buffer is empty
    is_empty = (checksum == 0)

    # Save number of bytes read and checksum to a file
    with open(output_filename, 'w') as f:
        f.write(f'Number of Bytes Read: {len(buffer)}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == "__main__":
    main()


Make sure to create an `input_file.txt` in the same directory where this script is run. This script reads the binary content, calculates a checksum using modulo 256 of the sum of byte values, and writes the number of bytes read along with the computed checksum to `output_file.txt`.