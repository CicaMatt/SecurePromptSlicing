import os

# Step 1: Create a file called secret.txt and write to it.
with open("secret.txt", "w") as file:
    file.write("This is a secret message.\n")

# Step 2: Change the permissions of the file to restrictive (read-only for owner).
os.chmod("secret.txt", 0o400)

# Step 3: Print the permissions of the file.
file_stat = os.stat("secret.txt")
permissions = oct(file_stat.st_mode)[-3:]
print(f"Permissions of secret.txt: {permissions}")