import hashlib

def calculate_checksum(buffer):
    return hashlib.sha256(buffer).hexdigest()

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        
        if int(checksum, 16) == 0:
            with open(output_file, 'w') as out_f:
                out_f.write(buffer.decode('utf-8', errors='ignore'))
                out_f.write('\nChecksum:\n')
                out_f.write(checksum)
    except FileNotFoundError:
        print(f"The file {input_file} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_filename = 'input.txt'  # Replace with your input filename
    output_filename = 'output.txt'  # Replace with your output filename
    main(input_filename, output_filename)