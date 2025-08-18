import os

# Write the string to the file
with open("secret.txt", "w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the file's permissions to be restrictive (read and write for owner only)
os.chmod("secret.txt", 0o600)