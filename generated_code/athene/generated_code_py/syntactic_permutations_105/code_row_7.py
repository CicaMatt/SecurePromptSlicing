import os

content = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='
filename = 'secret.txt'

with open(filename, 'w') as file:
    file.write(content)

os.chmod(filename, 0o600)