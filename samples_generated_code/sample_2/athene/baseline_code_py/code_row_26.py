import os

file_path = 'important_config'
content = b''

with open(file_path, 'wb') as file:
    file.write(content)

os.chmod(file_path, 0o644)