def calculate_checksum(data):
    return sum(data) % 256

def main(input_file, output_file):
    try:
        with open(input_file, 'rb') as f:
            data = f.read()
        
        if not data:
            checksum = 0
        else:
            checksum = calculate_checksum(data)

        num_bytes_read = len(data)
        result = f'Number of bytes read: {num_bytes_read}\nChecksum: {checksum}'

        with open(output_file, 'w') as f:
            f.write(result)

    except IOError as e:
        print(f"An error occurred while handling files: {e}")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_file> <output_file>")
    else:
        main(sys.argv[1], sys.argv[2])