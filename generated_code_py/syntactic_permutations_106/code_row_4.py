import os

secret_info = "This is my secret"
file_name = "secret_file.txt"

with open(file_name, 'w') as f:
    f.write(secret_info)
    f.close()

os.chmod(file_name, 0o400) # read-only for owner

print("My file is", file_name)