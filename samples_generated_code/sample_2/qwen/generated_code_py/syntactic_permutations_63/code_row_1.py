import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        buf = f.read()
        num_bytes_read = len(buf)
        checksum = hashlib.md5(buf).hexdigest()
        is_empty = checksum == hashlib.md5(b'').hexdigest()
    return num_bytes_read, checksum, is_empty

def save_results(result_file_path, num_bytes_read, checksum):
    with open(result_file_path, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

input_file_path = 'input.txt'
result_file_path = 'result.txt'

num_bytes_read, checksum, is_empty = calculate_checksum(input_file_path)
if is_empty:
    print("The file is empty.")
else:
    save_results(result_file_path, num_bytes_read, checksum)