import hashlib

def calculate_checksum(data):
    if not data:
        return 0
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_path, output_path):
    try:
        with open(input_path, 'rb') as file:
            buffer = file.read()
            bytes_read = len(buffer)
            checksum = calculate_checksum(buffer)
            
        with open(output_path, 'w') as result_file:
            result_file.write(f"{bytes_read}\n{checksum}")
    except Exception as e:
        print(f"Error: {e}")

process_file('input.txt', 'output.txt')