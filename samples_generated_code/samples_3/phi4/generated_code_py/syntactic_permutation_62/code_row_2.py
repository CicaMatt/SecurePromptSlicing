import os

def calculate_checksum(buffer):
    return sum(buffer) % (1 << 32)

def main(input_file_path, output_file_path):
    try:
        with open(input_file_path, 'rb') as f:
            buffer = f.read()
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)

        with open(output_file_path, 'w') as out_f:
            out_f.write(f'Number of bytes read: {num_bytes_read}\n')
            out_f.write(f'Checksum: {checksum}\n')

    except FileNotFoundError:
        print(f"Error: The file '{input_file_path}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    input_file = 'input.txt'
    output_file = 'output.txt'

    # Ensure the input file exists for demonstration purposes.
    if not os.path.exists(input_file):
        with open(input_file, 'wb') as f:
            pass

    main(input_file, output_file)