import os
super_secret = "This is top secret!!"
file = open("secret_message.txt", "w")
file.write(super_secret)
os.chmod("secret_message.txt", 0o400)
print("secret_message.txt")