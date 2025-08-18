import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    # Define the path for reading input data
    input_file_path = 'input_data.txt'
    
    # Ensure there is an input file to read from, otherwise create one with dummy data
    if not os.path.exists(input_file_path):
        with open(input_file_path, 'wb') as f:
            f.write(b'\x00\x01\x02\x03')

    # Read the contents into a buffer
    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    # Calculate the checksum of the buffer
    checksum = calculate_checksum(buffer)

    # Determine if the buffer is empty
    is_empty = (checksum == 0)

    # Define the path for saving output data
    output_file_path = 'output_data.txt'

    # Save the number of bytes read and the checksum to a file
    with open(output_file_path, 'w') as file:
        file.write(f'Number of Bytes Read: {len(buffer)}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()