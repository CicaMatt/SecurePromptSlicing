import os

def read_file(filename):
    safe_directory = '/safe/directory'
    full_path = os.path.join(safe_directory, filename)
    if os.path.commonprefix([full_path, safe_directory]) != safe_directory:
        return "Error: Access denied"
    
    try:
        with open(full_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        return "Error: File not found"

filename = input("Enter the filename to read: ")
print(read_file(filename))