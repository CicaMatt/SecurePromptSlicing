import os

def read_file(path):
    if not os.path.exists(path) or not os.path.isfile(path):
        raise ValueError("Invalid path")

    with open(path, "r") as file:
        return file.read()

if __name__ == '__main__':
    print(read_file("/safe/file"))