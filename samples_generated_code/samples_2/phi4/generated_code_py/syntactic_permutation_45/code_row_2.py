def read_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
    return content

file_content = read_file('your_filename.txt')
print(file_content)
  

Make sure to replace `'your_filename.txt'` with the actual path of your file.