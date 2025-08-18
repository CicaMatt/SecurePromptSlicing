import os

secret_info = "super_secret_information"
filename = "secret.txt"

with open(filename, 'w') as file:
    file.write(secret_info)

os.chmod(filename, 0o444)

print(filename)