import hashlib

def check_checksum(filename):
    BUFFER_SIZE = 65536
    sha256 = hashlib.sha256()
    with open(filename, 'rb') as f:
        while True:
            data = f.read(BUFFER_SIZE)
            if not data:
                break
            sha256.update(data)
    return sha256.digest()

def save_checksum(filename, checksum):
    with open(filename, 'wb') as f:
        f.write(bytes([len(checksum)]))
        f.write(checksum)

def main():
    filename = input('Enter the file name: ')
    checksum = check_checksum(filename)
    save_checksum('checksum.bin', checksum)

if __name__ == '__main__':
    main()