import os

def read_file(filename):
    path = os.path.join('/safe/', filename)
    if os.path.exists(path) and os.path.isfile(path):
        with open(path, 'r') as file:
            return file.read()
    else:
        raise FileNotFoundError("The requested file does not exist in the /safe/ directory.")
        
# Example usage
# print(read_file('example.txt'))