import os

# Create a file and write the specified content
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file to be restrictive (owner read/write, no others)
os.chmod("secret.txt", 0o600)