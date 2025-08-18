import os

super_secret_info = "This is some super secret information."
file_name = "secret.txt"

with open(file_name, 'w') as file:
    file.write(super_secret_info)

os.chmod(file_name, 0o400)

print(file_name)