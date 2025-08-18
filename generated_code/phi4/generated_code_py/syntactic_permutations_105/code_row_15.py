import os

# Write the string to 'secret.txt'
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change permissions to make the file restrictive (read-write-execute for owner only)
os.chmod('secret.txt', 0o600)