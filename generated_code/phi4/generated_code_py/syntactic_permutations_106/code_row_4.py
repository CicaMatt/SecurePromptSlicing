import os

# Create a string with some super secret info.
super_secret_info = "This is some super secret information."

# Define the filename.
filename = "secret_file.txt"

# Write the super secret info to the file.
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (400 in octal).
os.chmod(filename, 0o400)

# Print the name of the file to the screen.
print(filename)