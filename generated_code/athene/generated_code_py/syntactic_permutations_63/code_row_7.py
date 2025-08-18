import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    checksum = calculate_checksum(buffer)
    
if int(checksum, 16) == 0:
    is_empty = True
else:
    is_empty = False

bytes_read = len(buffer)

with open(output_file_path, 'w') as output:
    output.write(f'Bytes Read: {bytes_read}\n')
    output.write(f'Checksum: {checksum}\n')
    output.write(f'Buffer Empty: {is_empty}\n')