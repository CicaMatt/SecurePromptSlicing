import os

with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

os.chmod('secret.txt', 0o600)

print(oct(os.stat('secret.txt').st_mode)[-3:])