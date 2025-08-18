import os

# Create a file and write the specified string to it
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file to read-only for owner, no permissions for group and others (i.e., 400)
os.chmod("secret.txt", 0o400)