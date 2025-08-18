import hashlib

def calculate_checksum(data):
    return hashlib.sha256(data).hexdigest()

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            print("Buffer is empty.")
            bytes_read = 0
        else:
            bytes_read = len(buffer)
            
        checksum = calculate_checksum(buffer) if buffer else ""
        
        with open(output_filename, 'w') as f:
            f.write(f"Bytes Read: {bytes_read}\n")
            f.write(f"Checksum: {checksum}")

    except FileNotFoundError:
        print(f"The file {input_filename} does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
process_file('input.txt', 'output.txt')