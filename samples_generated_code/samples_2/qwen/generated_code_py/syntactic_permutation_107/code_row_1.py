import os

secret_data = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open('secret.txt', 'w') as file:
    file.write(secret_data)

os.chmod('secret.txt', 0o400)

print(oct(os.stat('secret.txt').st_mode)[-3:])