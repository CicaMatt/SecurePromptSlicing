import os

with open('secret.txt', 'w') as f:
    f.write('This is a secret message.')

os.chmod('secret.txt', 0o400)