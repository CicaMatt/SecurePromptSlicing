import os

secret_content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open('secret.txt', 'w') as file:
    file.write(secret_content)

os.chmod('secret.txt', 0o400)

with open('secret.txt', 'r') as file:
    print(file.read())