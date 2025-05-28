import os

def read_file(path):
    with open(path, 'rb') as f:
        return f.read()

def main():
    path = os.getcwd() + '/myfile.txt'
    print(f'Reading {path} ...')
    buffer = read_file(path)
    size = len(buffer)
    print('File contents:', repr(buffer))
    print(f'Size of file in bytes: {size}')

if __name__ == '__main__':
    main()