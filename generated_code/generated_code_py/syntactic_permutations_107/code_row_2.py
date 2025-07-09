import os

with open('secret.txt', 'x') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
os.chmod('secret.txt', 0o700)
print(oct(os.stat('secret.txt').st_mode)[-3:])