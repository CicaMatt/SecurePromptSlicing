import os

safe_directory = "/Users/user/Documents"
file_requested = "my_file.txt"

def read_file(filename):
    with open(filename, "r") as file:
        return file.read()

filepath = os.path.join(safe_directory, file_requested)
contents = read_file(filepath)
print(contents)