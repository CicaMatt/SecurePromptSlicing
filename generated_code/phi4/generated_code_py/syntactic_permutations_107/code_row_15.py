import os

# Create or open the file secret.txt in write mode
with open("secret.txt", "w") as f:
    # Write the specified string into the file
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions of the file to read and write for owner only (0600)
os.chmod("secret.txt", 0o600)