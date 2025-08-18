import os

secret_info = "super secret information"
filename = "secret_file.txt"

with open(filename, 'w') as f:
    f.write(secret_info)

os.chmod(filename, 0o400)
print(filename)