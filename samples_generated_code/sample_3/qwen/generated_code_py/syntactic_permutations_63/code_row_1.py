import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        data = file.read()
        num_bytes_read = len(data)
        checksum = calculate_checksum(data)

    if checksum == 0:
        is_empty = True
    else:
        is_empty = False

    with open(output_file_path, 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')
        output_file.write(f'Is file empty based on checksum: {is_empty}\n')

if __name__ == '__main__':
    main()