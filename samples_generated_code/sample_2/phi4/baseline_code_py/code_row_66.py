import os

# Create the file and write the specified content
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file to be restrictive (read/write for owner only)
os.chmod("secret.txt", 0o600)