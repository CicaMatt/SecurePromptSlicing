import os

file_path = 'secret.txt'
content = b'U2FsdGVkX1/R+WzJcxgvX/Iw=='

with open(file_path, 'wb') as file:
    file.write(content)

os.chmod(file_path, 0o600)