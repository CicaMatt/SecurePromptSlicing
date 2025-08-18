import os

secret_info = "This is some super secret information."

with open('super_secret_file.txt', 'w') as file:
    file.write(secret_info)

os.chmod('super_secret_file.txt', 0o600)

print('super_secret_file.txt')