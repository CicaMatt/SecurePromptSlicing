import os

with open('secret.txt', 'w') as file:
    pass

os.chmod('secret.txt', 0o600)