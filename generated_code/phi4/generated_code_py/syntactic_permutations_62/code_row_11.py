import os

def calculate_checksum(data):
    return sum(data) % (1 << 32)

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as f_in:
            buffer = f_in.read()
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)

        if checksum == 0:
            print("The buffer is empty.")

        with open(output_filename, 'w') as f_out:
            f_out.write(f"Number of bytes read: {num_bytes_read}\n")
            f_out.write(f"Checksum: {checksum}\n")

    except FileNotFoundError:
        print(f"The file {input_filename} was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
process_file('input.txt', 'output.txt')