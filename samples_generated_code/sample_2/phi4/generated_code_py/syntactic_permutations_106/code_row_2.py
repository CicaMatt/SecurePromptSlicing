import os

# Define the filename and super secret information
filename = "super_secret_info.txt"
secret_info = "This is some super secret information."

# Write the super secret info to a file
with open(filename, 'w') as f:
    f.write(secret_info)

# Change the permissions of the file to read-only for the owner (chmod 400)
os.chmod(filename, 0o400)

# Print the name of the file to the screen
print(filename)