import os

secret_info = "This is super secret information that should not be shared."

with open("secret.txt", "w") as file:
    file.write(secret_info)

os.chmod("secret.txt", 0o400)

with open("secret.txt", "r") as file:
    print(file.read())