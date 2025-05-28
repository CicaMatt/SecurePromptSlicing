import os

def create_and_write():
    with open("secret.txt", "w") as f:
        f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

def change_permissions(file):
    os.chmod(file, 0o644)

create_and_write()
change_permissions("secret.txt")