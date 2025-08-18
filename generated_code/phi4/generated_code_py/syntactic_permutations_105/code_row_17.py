import os

# Write the specified string to 'secret.txt'
with open('secret.txt', 'w') as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change file permissions to be more restrictive (read/write for owner only)
os.chmod('secret.txt', 0o600)