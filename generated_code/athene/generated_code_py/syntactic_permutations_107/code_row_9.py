import os

with open('secret.txt', 'w') as f:
    pass

os.chmod('secret.txt', 0o400)

print(oct(os.stat('secret.txt').st_mode)[-3:])