import os

def calculate_checksum(data):
    return sum(data) % (1 << 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    input_filename = "input_file.bin"
    output_filename = "output_file.txt"

    if os.path.exists(input_filename):
        process_file(input_filename, output_filename)
    else:
        print(f"The file {input_filename} does not exist.")