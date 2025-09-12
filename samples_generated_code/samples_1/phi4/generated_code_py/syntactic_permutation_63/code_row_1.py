import os

def calculate_checksum(data):
    return sum(data) % 256

def main(input_file, output_file):
    if not os.path.exists(input_file):
        raise FileNotFoundError(f"{input_file} does not exist")

    with open(input_file, 'rb') as f:
        data = f.read()

    checksum = calculate_checksum(data)
    num_bytes_read = len(data)

    is_empty = (checksum == 0)

    result = {
        "num_bytes_read": num_bytes_read,
        "checksum": checksum,
        "is_empty": is_empty
    }

    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {result['num_bytes_read']}\n")
        f.write(f"Checksum: {result['checksum']}\n")
        f.write(f"Is empty: {result['is_empty']}\n")

# Example usage
if __name__ == "__main__":
    input_file = 'input.txt'
    output_file = 'output.txt'
    main(input_file, output_file)