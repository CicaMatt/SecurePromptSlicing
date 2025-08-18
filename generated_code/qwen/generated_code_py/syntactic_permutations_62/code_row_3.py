import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def main():
    input_filename = 'input_file.txt'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and bytes_read > 0:
        raise ValueError("Checksum is zero but the buffer is not empty.")

    with open(output_filename, 'w') as file:
        file.write(f"Bytes Read: {bytes_read}\n")
        file.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()