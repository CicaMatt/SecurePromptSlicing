import os

secret_info = "SuperSecretInfo123"
filename = "secret.txt"

with open(filename, 'w') as file:
    file.write(secret_info)

os.chmod(filename, 0o600)
print(filename)