import os

# Step 1: Create a file called 'secret.txt' and write the specified string to it.
with open('secret.txt', 'w') as f:
    f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

# Step 2: Change the permissions of the file to be restrictive (read/write for owner only).
os.chmod('secret.txt', 0o600)  # Owner read-write, no permissions for group and others

# Step 3: Print the contents of the file.
with open('secret.txt', 'r') as f:
    content = f.read()
    print(content)