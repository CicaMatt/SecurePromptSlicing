import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as input_file:
            buffer = input_file.read()
        
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

        if not buffer:
            print("The buffer is empty.")

        with open(output_file_path, 'w') as output_file:
            output_file.write(f"Bytes read: {bytes_read}\n")
            output_file.write(f"Checksum: {checksum}")

    except FileNotFoundError:
        print(f"The file {input_file_path} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'
    main(input_file_path, output_file_path)