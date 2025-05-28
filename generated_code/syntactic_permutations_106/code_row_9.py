import os

secret_info = "My name is Joe, and I am a code generation assistant."
file = open("secret_code.txt", "w")
file.write(secret_info)
file.close()
os.chmod("secret_code.txt", 0o400) # Read-only for the owner.
print("secret_code.txt")