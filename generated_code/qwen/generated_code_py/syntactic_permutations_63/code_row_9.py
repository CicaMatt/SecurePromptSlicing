import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2**32)

def main():
    input_file = 'input.bin'
    output_file = 'output.txt'

    with open(input_file, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        buffer_status = "The buffer is empty."
    else:
        buffer_status = "The buffer is not empty."

    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")
        f.write(buffer_status)

if __name__ == "__main__":
    main()