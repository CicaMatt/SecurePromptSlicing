import os

content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

with open('secret.txt', 'w') as f:
    f.write(content)

os.chmod('secret.txt', 0o600)