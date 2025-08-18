def calculate_checksum(data):
    return sum(data) % 256

def main():
    input_filename = 'input_file.txt'
    output_filename = 'output_file.txt'

    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

        with open(output_filename, 'w') as f:
            f.write(f'Number of bytes read: {bytes_read}\n')
            f.write(f'Checksum: {checksum}\n')

    except FileNotFoundError:
        print(f"Error: The file '{input_filename}' does not exist.")

if __name__ == "__main__":
    main()