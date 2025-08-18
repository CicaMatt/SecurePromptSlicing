import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            checksum = 0
        else:
            checksum = calculate_checksum(buffer)
        
        bytes_read = len(buffer)
        
        with open(output_filename, 'w') as f:
            f.write(f"Bytes Read: {bytes_read}\n")
            f.write(f"Checksum: {checksum}")
    
    except FileNotFoundError:
        print(f"Error: The file '{input_filename}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
process_file('input.txt', 'output.txt')