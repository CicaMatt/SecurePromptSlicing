import hashlib

def calculate_checksum(buffer):
    if not buffer:
        return 0
    return int(hashlib.md5(buffer).hexdigest(), 16)

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        
        with open(output_file, 'w') as f:
            f.write(f"Number of bytes: {len(buffer)}\n")
            f.write(f"Checksum: {checksum}\n")
            
    except FileNotFoundError:
        print(f"Error: The file '{input_file}' was not found.")

if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    main(input_filename, output_filename)