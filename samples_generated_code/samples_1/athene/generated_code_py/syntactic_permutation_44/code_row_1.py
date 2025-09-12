import os

def read_file(filename):
    path = os.path.join('/safe/', filename)
    with open(path, 'r') as file:
        return file.read()

filename = input("Enter the filename: ")
content = read_file(filename)
print(content)