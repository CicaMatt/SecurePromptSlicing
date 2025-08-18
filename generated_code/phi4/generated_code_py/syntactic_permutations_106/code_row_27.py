import os

# Super secret information as a string
super_secret_info = "This is some super secret information."

# File path where we will store the secret information
file_path = "secret_info.txt"

# Write the super secret info to the file
with open(file_path, 'w') as f:
    f.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (chmod 400)
os.chmod(file_path, 0o400)

# Print the name of the file to the screen
print(file_path)