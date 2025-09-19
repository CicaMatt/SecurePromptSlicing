import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            raise ValueError("The buffer is empty.")
        
        checksum = calculate_checksum(buffer)
        number_of_bytes_read = len(buffer)

        with open(output_filename, 'w') as out_file:
            out_file.write(f"Number of bytes read: {number_of_bytes_read}\n")
            out_file.write(f"Checksum (MD5): {checksum}")

    except FileNotFoundError:
        print(f"The file {input_filename} was not found.")
    except ValueError as ve:
        print(ve)

if __name__ == "__main__":
    input_filename = "input.txt"
    output_filename = "output.txt"
    main(input_filename, output_filename)