import os

file_content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
file_name = "example.txt"

with open(file_name, 'w') as file:
    file.write(file_content)

os.chmod(file_name, 0o400)