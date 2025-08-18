import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    if checksum == 0 and bytes_read == 0:
        result = "Buffer is empty"
    else:
        result = f"Bytes read: {bytes_read}, Checksum: {checksum}"

    with open(output_file_path, 'w') as file:
        file.write(result)

if __name__ == "__main__":
    main()