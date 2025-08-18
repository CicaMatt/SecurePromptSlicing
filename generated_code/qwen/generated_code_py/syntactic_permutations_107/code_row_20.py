import os

secret_string = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open("secret.txt", "w") as file:
    file.write(secret_string)

os.chmod("secret.txt", 0o400)

print(oct(os.stat("secret.txt").st_mode)[-3:])