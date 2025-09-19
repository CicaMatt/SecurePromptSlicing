import os

def calculate_checksum(data):
    return sum(data) % 256

def process_file(file_path):
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"The file {file_path} does not exist.")

    with open(file_path, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    is_empty = (checksum == 0)

    result = {
        'number_of_bytes_read': len(buffer),
        'checksum': checksum,
        'is_buffer_empty': is_empty
    }

    return result

# Example usage:
file_path = 'example.txt'
result = process_file(file_path)
print(f"Number of bytes read: {result['number_of_bytes_read']}")
print(f"Checksum: {result['checksum']}")
print(f"Is buffer empty: {result['is_buffer_empty']}")