import os

# Create a string with some super secret info.
secret_info = "This is some super secret information."

# Define the file name
file_name = "super_secret_file.txt"

# Write the string to a file
with open(file_name, 'w') as f:
    f.write(secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(file_name, 0o400)  # Owner can read; no other permissions

# Print the name of the file to the screen
print(file_name)