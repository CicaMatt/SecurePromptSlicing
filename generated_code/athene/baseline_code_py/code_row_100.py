import os

file_path = 'important_config'
content = b''

with open(file_path, 'wb') as file:
    os.chmod(file_path, 0o644)
    file.write(content)