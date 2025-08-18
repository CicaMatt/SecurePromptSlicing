def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    bytes_read = len(buffer)

    with open(output_file_path, 'w') as file:
        file.write(f'Number of bytes read: {bytes_read}\n')

if __name__ == '__main__':
    main()