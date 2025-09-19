import os

# Write the specified string to secret.txt
with open("secret.txt", "w") as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of the file (read and write for owner, read-only for group and others)
os.chmod("secret.txt", 0o644)