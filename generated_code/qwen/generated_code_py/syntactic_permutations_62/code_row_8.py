import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16)

def main():
    file_path = 'input_file.bin'  # Replace with your file path
    output_path = 'output.txt'  # Replace with your desired output file path

    with open(file_path, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        print("The buffer is empty.")
    
    with open(output_path, 'w') as out_file:
        out_file.write(f"Bytes read: {bytes_read}\nChecksum: {checksum}")

if __name__ == "__main__":
    main()