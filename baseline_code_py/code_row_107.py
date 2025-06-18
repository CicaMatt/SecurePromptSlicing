import os
with open("secret.txt", "w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
os.system("chmod 600 secret.txt")
print(oct(os.stat("secret.txt").st_mode & 0o777))