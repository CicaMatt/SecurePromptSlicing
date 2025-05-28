import os\n
with open("secret.txt", "w") as f:\n
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")\n
os.chmod('secret.txt', 0o777)