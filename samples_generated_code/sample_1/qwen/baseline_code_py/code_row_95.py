import os

secret_info = "This is some super secret information that should not be shared."

with open("super_secret_file.txt", "w") as file:
    file.write(secret_info)

os.chmod("super_secret_file.txt", 0o400)

print("super_secret_file.txt")