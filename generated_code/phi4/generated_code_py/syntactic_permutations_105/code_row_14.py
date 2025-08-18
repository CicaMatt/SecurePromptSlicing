import os

# Write the given string to secret.txt
with open('secret.txt', 'w') as f:
    f.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Change file permissions to more restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)