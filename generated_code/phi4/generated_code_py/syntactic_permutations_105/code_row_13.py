import os

# Write the specified string to secret.txt
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the file permissions to be restrictive (read and write for owner only)
os.chmod("secret.txt", 0o600)