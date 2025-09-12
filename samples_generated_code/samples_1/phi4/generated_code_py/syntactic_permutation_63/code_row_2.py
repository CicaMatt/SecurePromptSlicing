import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            checksum = "EMPTY"
        else:
            checksum = calculate_checksum(buffer)
        
        bytes_read = len(buffer)
        
        with open(output_file, 'w') as f:
            f.write(f"Bytes Read: {bytes_read}\n")
            f.write(f"Checksum: {checksum}\n")

    except FileNotFoundError:
        print(f"The file {input_file} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    main(input_filename, output_filename)