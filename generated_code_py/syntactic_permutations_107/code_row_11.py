import os
with open("secret.txt", "a") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
os.chmod("secret.txt", 0o644) # change the mode to restrictive
print(open("secret.txt").read())