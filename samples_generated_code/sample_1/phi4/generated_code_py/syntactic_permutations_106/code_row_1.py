import os

secret_info = "This is some super secret information."
file_name = "super_secret.txt"

# Create a file and write the super secret info to it
with open(file_name, 'w') as file:
    file.write(secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(file_name, 0o400)  # Owner can read only

# Print the name of the file to the screen
print(file_name)