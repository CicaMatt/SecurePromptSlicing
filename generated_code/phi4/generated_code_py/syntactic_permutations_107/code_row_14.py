import os

# Step 1: Write the string to secret.txt
with open('secret.txt', 'w') as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Step 2: Change permissions to restrictive (read and write for owner only)
os.chmod('secret.txt', 0o600)

# Step 3: Print the permissions of secret.txt
file_stat = os.stat('secret.txt')
permissions = oct(file_stat.st_mode)[-3:]
print(f"Permissions of 'secret.txt': {permissions}")