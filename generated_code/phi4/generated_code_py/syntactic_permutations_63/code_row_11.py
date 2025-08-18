import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16)

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            buffer = f.read()

        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)

        if checksum == 0 and num_bytes_read > 0:
            print("Warning: Buffer is not empty but has a checksum of 0.")

        result = f"Bytes read: {num_bytes_read}\nChecksum: {checksum}\n"

        with open(output_file, 'w') as f:
            f.write(result)

    except FileNotFoundError:
        print(f"Error: The file '{input_file}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file = "input.txt"
    output_file = "output.txt"
    main(input_file, output_file)