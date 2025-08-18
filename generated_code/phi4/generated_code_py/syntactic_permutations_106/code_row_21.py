import os

# Define the super secret information as a string
super_secret_info = "This is some super secret information."

# Create a filename
filename = "secret_file.txt"

# Write the super secret info to the file
with open(filename, 'w') as f:
    f.write(super_secret_info)

# Change the permissions of the file to be read/write for the owner only
os.chmod(filename, 0o600)

# Print the name of the file to the screen
print(f"The file is: {filename}")