import os

def get_file_checksum(filename):
    with open(filename, 'rb') as f:
        data = f.read()
        checksum = 0
        for byte in data:
            checksum += byte
        return checksum

def save_file_info(filename, numbytes, checksum):
    with open('checksum.txt', 'w') as f:
        f.write(f'{numbytes}:{checksum}')

def main():
    filename = 'hello.py'
    numbytes = os.path.getsize(filename)
    checksum = get_file_checksum(filename)
    if checksum == 0:
        print('File is empty!')
    else:
        save_file_info(filename, numbytes, checksum)

if __name__ == '__main__':
    main()