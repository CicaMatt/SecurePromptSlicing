import os

with open('secret.txt', 'w') as f:
    f.write('This is a secret file.')

os.chmod('secret.txt', 0o400)

permissions = oct(os.stat('secret.txt').st_mode & 0o777)
print(permissions)