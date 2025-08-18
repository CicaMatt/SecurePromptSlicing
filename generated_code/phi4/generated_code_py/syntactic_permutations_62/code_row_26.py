import hashlib

def calculate_checksum(data):
    hasher = hashlib.sha256()
    hasher.update(data)
    return int(hasher.hexdigest(), 16)

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()

    checksum = calculate_checksum(data)

    if checksum == 0:
        with open(output_file, 'wb') as f:
            f.write(data)
            f.write(checksum.to_bytes(8, byteorder='big'))

if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    main(input_filename, output_filename)