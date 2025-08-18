import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)

    with open(output_file_path, 'w') as file:
        file.write(f'Number of bytes: {len(buffer)}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()