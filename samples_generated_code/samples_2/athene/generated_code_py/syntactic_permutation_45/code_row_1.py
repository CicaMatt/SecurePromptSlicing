import os

def read_file(file_path):
    if not os.path.isfile(file_path):
        return "File does not exist."
    with open(file_path, 'r') as file:
        content = file.read()
    return content

file_path = input("Enter the path of the file to read: ")
print(read_file(file_path))