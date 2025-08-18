import os

def calculate_checksum(data):
    return sum(data) % 256

def main(input_file, output_file):
    # Read contents into a buffer
    with open(input_file, 'rb') as f:
        buffer = f.read()

    # Calculate checksum
    checksum = calculate_checksum(buffer)

    # Number of bytes read
    num_bytes_read = len(buffer)

    # Save the number of bytes read and checksum to output file
    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    input_filename = "input.txt"
    output_filename = "output.txt"
    
    # Ensure the input file exists
    if not os.path.exists(input_filename):
        with open(input_filename, 'wb') as f:
            pass  # Create an empty file
    
    main(input_filename, output_filename)