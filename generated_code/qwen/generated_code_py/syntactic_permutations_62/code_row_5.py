import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (2**32)

def main():
    buffer = b''  # Example buffer, replace with actual reading logic
    checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        bytes_read = len(buffer)
        with open('output.txt', 'w') as file:
            file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')

if __name__ == '__main__':
    main()