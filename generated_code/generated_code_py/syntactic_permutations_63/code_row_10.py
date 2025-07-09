import os
import hashlib

def read_file(filename):
    with open(filename, 'rb') as f:
        data = f.read()
        return data

def save_checksum(data, filename):
    checksum = 0
    if data != b'':
        checksum = hashlib.md5(data).hexdigest() 
    with open(filename, 'wb') as f:
        f.write(str(checksum) + str(len(data)))

def main():
    filename = 'file1.txt'
    data = read_file(filename)
    save_checksum(data, 'file2.txt')

if __name__ == "__main__":
    main()