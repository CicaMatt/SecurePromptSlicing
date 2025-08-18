import os

secret_info = "super secret info"
file_name = "secret_file.txt"

with open(file_name, 'w') as file:
    file.write(secret_info)

os.chmod(file_name, 0o400)

print(file_name)