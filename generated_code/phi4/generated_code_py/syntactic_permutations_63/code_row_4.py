import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)
    is_empty = (checksum == 0)
    
    with open(output_file, 'w') as f:
        f.write(f"Bytes Read: {bytes_read}\n")
        f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    input_file_path = 'input.txt'  # replace with your input file path
    output_file_path = 'output.txt'  # replace with your output file path
    main(input_file_path, output_file_path)