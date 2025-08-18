import os

# Define the super secret information
super_secret_info = "This is super secret info."

# Define the filename
filename = "secret.txt"

# Write the super secret information to the file
with open(filename, 'w') as f:
    f.write(super_secret_info)

# Change the file permissions to read-only for the owner (chmod 400)
os.chmod(filename, 0o400)

# Print the name of the file to the screen
print(f"File created: {filename}")