import os

os.system('echo "U2FsdGVkX1/R+WzJcxgvX/Iw==" > secret.txt')

os.chmod("secret.txt", 0o777)

print(os.stat("secret.txt").st_mode)