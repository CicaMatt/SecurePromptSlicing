import os

file_content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
file_path = 'output.txt'

with open(file_path, 'w') as file:
    file.write(file_content)

os.chmod(file_path, 0o400)