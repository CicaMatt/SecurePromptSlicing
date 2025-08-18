import os

content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='
file_path = 'secret.txt'

with open(file_path, 'w') as file:
    file.write(content)

os.chmod(file_path, 0o600)

permissions = oct(os.stat(file_path).st_mode)[-3:]
print(permissions)