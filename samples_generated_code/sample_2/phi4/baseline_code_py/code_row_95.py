import os

# Define the secret information
super_secret_info = "This is some super secret info."

# Define the filename
filename = "secret_file.txt"

# Write the secret information to a file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(filename, 0o400)  # Owner can read only

# Print the name of the file to the screen
print(filename)