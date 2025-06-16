import os

secret_info = "This is some super secret information."

with open("super_secret_file.txt", 'w') as fh:
    fh.write(secret_info)
os.chmod("super_secret_file.txt", 0o444)
print("super_secret_file.txt")