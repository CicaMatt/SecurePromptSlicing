import os

filename = 'example.txt'
with open(filename, 'w') as file:
    os.chmod(filename, 0o644)