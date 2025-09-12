import os

# Write the specified content to secret.txt
with open('secret.txt', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change permissions to be more restrictive (read and write for owner, no permissions for others)
os.chmod('secret.txt', 0o600)