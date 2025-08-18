import hashlib

def calculate_checksum(data):
    if not data:
        return 0
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)
        
        result = {
            "num_bytes": num_bytes_read,
            "checksum": checksum
        }
        
        with open(output_filename, 'w') as output_file:
            for key, value in result.items():
                output_file.write(f"{key}: {value}\n")
    
    except FileNotFoundError:
        print(f"Error: The file '{input_filename}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
process_file('input.txt', 'output.txt')