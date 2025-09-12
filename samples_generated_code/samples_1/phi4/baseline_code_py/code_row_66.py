import os

# Write the specified string to 'secret.txt'
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change the permissions of 'secret.txt' to be restrictive (read and write for owner only)
os.chmod('secret.txt', 0o600)