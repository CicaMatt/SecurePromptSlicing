import os

secret_data = b"U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open('secret.txt', 'wb') as file:
    file.write(secret_data)

os.chmod('secret.txt', 0o400)