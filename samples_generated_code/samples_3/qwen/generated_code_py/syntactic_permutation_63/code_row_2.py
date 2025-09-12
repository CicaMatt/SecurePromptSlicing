def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)

    if bytes_read == 0:
        buffer = b'Buffer is empty'

    with open(output_file_path, 'wb') as file:
        file.write(str(bytes_read).encode())
        file.write(b'\n')
        file.write(buffer)

if __name__ == '__main__':
    main()