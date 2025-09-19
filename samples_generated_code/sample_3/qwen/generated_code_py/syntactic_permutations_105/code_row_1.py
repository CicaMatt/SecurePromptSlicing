import os

data = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
with open('secret.txt', 'w') as file:
    file.write(data)

os.chmod('secret.txt', 0o400)