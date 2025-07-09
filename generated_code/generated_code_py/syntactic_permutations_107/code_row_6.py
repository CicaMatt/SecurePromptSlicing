import os
os.system("echo 'U2FsdGVkX1/R+WzJcxgvX/Iw==' > secret.txt")
os.system("chmod 600 secret.txt")
print(os.stat("secret.txt").st_mode)