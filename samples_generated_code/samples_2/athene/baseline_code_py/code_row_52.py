import os

content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
with open('secret.txt', 'w') as f:
    f.write(content)

os.chmod('secret.txt', 0o600)
print(oct(os.stat('secret.txt').st_mode)[-3:])