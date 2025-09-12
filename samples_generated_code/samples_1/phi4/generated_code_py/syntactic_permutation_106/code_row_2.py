import os

# Define the super secret information
super_secret_info = "This is some super secret info."

# Define the filename
filename = "secret.txt"

# Write the super secret info to a file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (read and write for owner, none for others)
os.chmod(filename, 0o400)

# Print the name of the file to the screen
print(filename)