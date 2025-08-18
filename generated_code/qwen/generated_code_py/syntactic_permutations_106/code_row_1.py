import os

secret_info = "This is some super secret information."
file_name = "super_secret.txt"

with open(file_name, 'w') as file:
    file.write(secret_info)

os.chmod(file_name, 0o400)

print(file_name)