import os

def calculate_checksum(buffer):
    return sum(buffer) & 0xFF

def main():
    input_file_path = 'input.bin'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = bytearray(file.read())

    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    if checksum == 0 and bytes_read == 0:
        result = "Buffer is empty.\n"
    else:
        result = f"Bytes read: {bytes_read}, Checksum: {checksum}\n"

    with open(output_file_path, 'w') as output_file:
        output_file.write(result)

if __name__ == "__main__":
    main()