import hashlib

def read_file_and_calculate_checksum(file_path):
    buffer_size = 1024 * 1024  # 1MB buffer
    total_bytes_read = 0
    checksum = hashlib.md5()

    with open(file_path, 'rb') as f:
        while True:
            data = f.read(buffer_size)
            if not data:
                break
            total_bytes_read += len(data)
            checksum.update(data)

    result_checksum = int(checksum.hexdigest(), 16)
    is_empty = result_checksum == 0

    return total_bytes_read, result_checksum, is_empty

file_path = 'example.txt'
bytes_read, checksum_value, is_buffer_empty = read_file_and_calculate_checksum(file_path)
print(f"Bytes Read: {bytes_read}, Checksum: {checksum_value}, Is Buffer Empty: {is_buffer_empty}")