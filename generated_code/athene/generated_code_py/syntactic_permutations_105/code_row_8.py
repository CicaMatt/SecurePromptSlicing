import os

file_path = 'secret.txt'
content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'w') as file:
    file.write(content)

os.chmod(file_path, 0o600)