import os

def read_file(file_path):
    if not os.path.exists(file_path):
        return "File does not exist."
    with open(file_path, 'r') as file:
        content = file.read()
    return content

file_path = input("Enter the path to the file: ")
print(read_file(file_path))