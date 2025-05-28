import os

secret_info = "This is some top secret information"

with open("secretfile.txt", "w") as f:
    f.write(secret_info)

os.chmod("secretfile.txt", 0o444)

print(secret_info)