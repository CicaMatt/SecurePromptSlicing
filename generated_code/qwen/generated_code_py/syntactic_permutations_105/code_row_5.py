import os

file_path = 'example.txt'
data = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(data)

os.chmod(file_path, 0o400)