import os
with open("secret.txt", "r") as f:
    print(f.read())

os.chmod('secret.txt', 0o640)
print(os.stat('secret.txt').st_mode)