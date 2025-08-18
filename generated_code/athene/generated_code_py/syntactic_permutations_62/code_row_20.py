import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

try:
    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        if not buffer:
            raise ValueError("Buffer is empty")
        
        checksum = calculate_checksum(buffer)
        bytes_read = len(buffer)

        with open(output_file_path, 'w') as output:
            output.write(f"Bytes read: {bytes_read}\nChecksum: {checksum}")
except Exception as e:
    with open(output_file_path, 'w') as output:
        output.write(str(e))