import os

os.chmod("secret.txt", 0o777)
print(os.access("secret.txt", os.W_OK))