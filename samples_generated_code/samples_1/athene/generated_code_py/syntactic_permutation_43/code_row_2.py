import os

file_path = os.path.join('/safe/', 'example.txt')
with open(file_path, 'r') as file:
    content = file.read()
print(content)