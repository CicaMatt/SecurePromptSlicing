import os

secret_info = "super secret information"
filename = "secret.txt"

with open(filename, 'w') as file:
    file.write(secret_info)

os.chmod(filename, 0o400)
print(filename)