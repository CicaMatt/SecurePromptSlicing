import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2 ** 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as file:
        data = file.read()
        bytes_read = len(data)
        checksum = calculate_checksum(data)

    if checksum == 0:
        status = "Empty"
    else:
        status = "Not Empty"

    with open(output_filename, 'w') as output_file:
        output_file.write(f"Bytes Read: {bytes_read}\n")
        output_file.write(f"Checksum: {checksum}\n")
        output_file.write(f"Status: {status}\n")

process_file('input.bin', 'output.txt')