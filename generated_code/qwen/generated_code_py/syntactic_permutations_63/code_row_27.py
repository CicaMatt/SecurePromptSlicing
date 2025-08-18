import hashlib

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as f:
        buffer = bytearray(f.read())

    checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes: {len(buffer)}\n")
        f.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()