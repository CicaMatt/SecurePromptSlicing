import os
file = open("secret.txt", "w")
file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")
file.close()
os.chmod("secret.txt", 0o444)