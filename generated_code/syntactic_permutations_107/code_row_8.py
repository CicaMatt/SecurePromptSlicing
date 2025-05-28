import os
with open('secret.txt', 'w+') as f:
    f.write('This is a secret')
os.chmod('secret.txt', 0o644)  # set read/write for owner, and only read for others
print(oct(os.stat('secret.txt').st_mode))