import os

# Create the file and write the specified content
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Change the permissions of the file to be restrictive (owner read/write, others no permission)
os.chmod('secret.txt', 0o600)