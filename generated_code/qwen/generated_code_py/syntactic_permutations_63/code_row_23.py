import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main():
    input_file = 'input.txt'
    output_file = 'output.txt'

    with open(input_file, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)

    if int(checksum, 16) == 0:
        with open(output_file, 'wb') as f:
            f.write(buffer)
            f.write(checksum.encode())

if __name__ == '__main__':
    main()