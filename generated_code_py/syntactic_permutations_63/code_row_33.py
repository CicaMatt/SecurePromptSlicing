import hashlib
def get_checksum(filename):
    with open(filename, 'rb') as f:
        data = f.read()
    return hashlib.md5(data).hexdigest()

def save_results(buffer, num_bytes, checksum):
    with open('checksum.txt', 'w') as outfile:
        outfile.write(f'{num_bytes} {checksum}\n')