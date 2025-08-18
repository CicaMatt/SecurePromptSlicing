import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def main():
    input_filename = 'input_file.txt'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and num_bytes_read > 0:
        raise ValueError("Checksum is zero but file is not empty.")

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()