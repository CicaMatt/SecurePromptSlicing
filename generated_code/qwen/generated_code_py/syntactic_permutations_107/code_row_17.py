import os

with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

os.chmod('secret.txt', 0o400)
print('.')