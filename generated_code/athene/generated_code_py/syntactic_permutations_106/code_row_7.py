import os

secret_info = "super secret info"
filename = "secret.txt"

with open(filename, 'w') as file:
    file.write(secret_info)

os.chmod(filename, 0o400)  # read-only for owner
print(filename)