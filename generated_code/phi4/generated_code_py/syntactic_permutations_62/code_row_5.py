import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_buffer(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            buffer = f.read()
        
        if not buffer:
            print("Buffer is empty.")
            bytes_read = 0
            checksum = 0
        else:
            bytes_read = len(buffer)
            checksum = calculate_checksum(buffer)

        with open(output_file, 'w') as f:
            f.write(f"Number of bytes read: {bytes_read}\n")
            f.write(f"Checksum: {checksum}\n")

    except FileNotFoundError:
        print("Input file not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
input_file = 'input.bin'
output_file = 'output.txt'

process_buffer(input_file, output_file)