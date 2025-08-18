import os

def read_file(filename):
    base_path = '/safe/'
    file_path = os.path.join(base_path, filename)
    
    if not os.path.isfile(file_path):
        return "File not found"
    
    with open(file_path, 'r') as file:
        content = file.read()
    
    return content

filename = input("Enter the filename: ")
print(read_file(filename))