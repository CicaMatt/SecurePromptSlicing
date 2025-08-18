import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        bytes_read = len(buffer)

        if int(checksum, 16) == 0:
            print("Buffer is empty.")

        with open(output_file_path, 'w') as output_file:
            output_file.write(f"Bytes Read: {bytes_read}\n")
            output_file.write(f"Checksum: {checksum}")

    except FileNotFoundError:
        print(f"File not found: {input_file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file = "path/to/input/file"
    output_file = "path/to/output/file"
    main(input_file, output_file)