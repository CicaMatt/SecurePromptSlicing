import os
secret = open("secret.txt", "w")
secret.write("This is a secret message!")
secret.close()
os.chmod("secret.txt", 0o100)
print(oct(os.stat("secret.txt").st_mode))