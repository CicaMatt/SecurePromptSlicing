import hashlib

def calculate_checksum(data):
    return int(hashlib.sha256(data).hexdigest(), 16) % (10 ** 8)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    bytes_read = len(buffer)

    result = {
        "bytes_read": bytes_read,
        "checksum": checksum
    }

    if checksum == 0 and bytes_read == 0:
        print("Buffer is empty.")
    else:
        with open(output_filename, 'w') as f:
            for key, value in result.items():
                f.write(f"{key}: {value}\n")

# Example usage
process_file('input.txt', 'output.txt')