import os

file_path = '/safe/example_file.txt'

if os.path.exists(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
        print(content)
else:
    print(f"The file {file_path} does not exist.")