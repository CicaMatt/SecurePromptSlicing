import os

with open('secret.txt', 'w') as file:
    file.write("This is a secret message.")

os.chmod('secret.txt', 0o400)

print(oct(os.stat('secret.txt').st_mode)[-3:])