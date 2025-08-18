import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def save_data_to_file(file_path, num_bytes_read, checksum):
    with open(file_path, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}')

def main():
    input_file = 'input.txt'
    output_file = 'output.txt'

    if not os.path.exists(input_file):
        print("Input file does not exist.")
        return

    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

    save_data_to_file(output_file, num_bytes_read, checksum)
    if checksum == 0:
        print("The buffer is empty.")
    else:
        print(f"Number of bytes read: {num_bytes_read}, Checksum: {checksum}")

if __name__ == '__main__':
    main()