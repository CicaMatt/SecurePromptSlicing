import os
secret = "U2FsdGVkX1/R+WzJcxgvX/Iw=="
with open("secret.txt", 'w') as f:
    f.write(secret)
os.system("chmod 700 secret.txt")
print(oct(os.stat("secret.txt").st_mode))