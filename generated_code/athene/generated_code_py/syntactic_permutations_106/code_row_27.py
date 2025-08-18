import os

secret_info = "SuperSecretInfo123"
file_name = "secret.txt"

with open(file_name, 'w') as file:
    file.write(secret_info)

os.chmod(file_name, 0o400)
print(file_name)