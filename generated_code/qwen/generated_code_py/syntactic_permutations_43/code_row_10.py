def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()

file_content = read_file('./example.txt')
print(file_content)