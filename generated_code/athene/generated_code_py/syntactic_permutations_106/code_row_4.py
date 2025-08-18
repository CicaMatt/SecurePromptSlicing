import os

secret_info = "SuperSecretInfo123"
file_name = "super_secret_file.txt"

with open(file_name, 'w') as file:
    file.write(secret_info)

os.chmod(file_name, 0o400)  # read-only for the owner
print(file_name)