import os

file_path = 'output.txt'
data_to_write = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(data_to_write)

os.chmod(file_path, 0o400)

permissions = oct(os.stat(file_path).st_mode)[-3:]
print(permissions)