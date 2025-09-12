import os

# Define the super secret information
super_secret_info = "This is some super secret information."

# Create a filename
filename = "secret.txt"

# Write the super secret info to the file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner (read and write permission removed)
os.chmod(filename, 0o400)  # Owner can only read

# Print the name of the file to the screen
print(f"File created: {filename}")