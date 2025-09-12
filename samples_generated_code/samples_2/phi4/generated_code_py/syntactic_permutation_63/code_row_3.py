import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main(input_file, output_file):
    if not os.path.exists(input_file):
        print(f"File {input_file} does not exist.")
        return
    
    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    is_empty = checksum == 0
    num_bytes_read = len(buffer)

    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")
        if is_empty:
            f.write("Buffer is empty.\n")
        else:
            f.write("Buffer is not empty.\n")

# Example usage
input_file = 'input.txt'
output_file = 'output.txt'
main(input_file, output_file)