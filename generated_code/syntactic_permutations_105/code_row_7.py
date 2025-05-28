import os

with open('file.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
os.chmod('file.txt', 0o700)