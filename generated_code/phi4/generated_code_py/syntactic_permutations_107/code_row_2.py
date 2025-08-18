import os

# Step 1: Create a file called secret.txt and write the given string into it
with open("secret.txt", "w") as file:
    file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==")

# Step 2: Change permissions of the file to restrictive (read & write for owner only)
os.chmod("secret.txt", 0o600)

# Step 3: Print the permissions of the file
file_permissions = oct(os.stat("secret.txt").st_mode)[-3:]
print(f"Permissions of 'secret.txt': {file_permissions}")