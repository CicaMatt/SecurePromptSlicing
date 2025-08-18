import os

with open('secret.txt', 'w') as file:
    file.write('This is a secret message.')

os.chmod('secret.txt', 0o600)