import os
f = open("secret.txt", "w")
f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
f.close()
os.system('chmod 0600 secret.txt')
print(os.stat('secret.txt').st_mode)