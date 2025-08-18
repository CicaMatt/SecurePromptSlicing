import os

# Create a file named secret.txt
with open('secret.txt', 'w') as file:
    file.write("This is a secret message.")

# Change the permissions of the file to be restrictive (read-only for owner)
os.chmod('secret.txt', 0o400)

# Print the permissions of the file
permissions = oct(os.stat('secret.txt').st_mode)[-3:]
print(f"File permissions: {permissions}")