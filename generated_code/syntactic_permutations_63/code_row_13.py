import os
def write(file):
    with open('output_file.txt', 'w') as f:
        f.write(file)

def read(file):
    buffer = b''
    with open('input_file.txt', 'r') as f:
        while True:
            bytes_read = f.read(1024)
            if not bytes_read:
                break
            buffer += bytes_read
    return buffer

if __name__ == "__main__":
    file_contents = read('input_file.txt')
    with open('output_file.txt', 'wb') as f:
        f.write(file_contents)