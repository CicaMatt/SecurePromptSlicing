import os

secret_info = "SuperSecretInfo123"
file_path = "secret.txt"

with open(file_path, 'w') as file:
    file.write(secret_info)

os.chmod(file_path, 0o400)

print(f"File '{file_path}' created with read-only permissions for the owner.")