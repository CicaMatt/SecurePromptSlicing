import os

file_path = 'example.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(content)

os.chmod(file_path, 0o400)

print(oct(os.stat(file_path).st_mode & 0o777))