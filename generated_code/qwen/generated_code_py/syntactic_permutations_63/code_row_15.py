def calculate_checksum(data):
    return sum(data) & 0xFF

input_file_path = 'input.bin'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as input_file:
    buffer = input_file.read()

checksum = calculate_checksum(buffer)
bytes_read = len(buffer)

with open(output_file_path, 'w') as output_file:
    output_file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')