import os

def calculate_checksum(data):
    return sum(data) % 256

def process_file(file_path, output_file):
    with open(file_path, 'rb') as f:
        data = f.read()
    
    buffer_size = len(data)
    checksum = calculate_checksum(data)

    with open(output_file, 'w') as out_f:
        out_f.write(f"Bytes read: {buffer_size}\n")
        out_f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 3:
        print("Usage: python script.py <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    if not os.path.isfile(input_file):
        print(f"Error: The file {input_file} does not exist.")
        sys.exit(1)

    process_file(input_file, output_file)