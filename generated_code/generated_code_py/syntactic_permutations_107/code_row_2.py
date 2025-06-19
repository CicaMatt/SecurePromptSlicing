import os

with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

os.chmod('secret.txt', 0o755)

print(os.stat('secret.txt').st_mode & 0b111111111)