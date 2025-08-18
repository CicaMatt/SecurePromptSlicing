import os

# Create a string with some super secret info.
secret_info = "This is some super secret information."

# Specify the filename
filename = "super_secret.txt"

# Write the secret info to the file
with open(filename, 'w') as f:
    f.write(secret_info)

# Change permissions of the file to read-only for the owner (chmod 400)
os.chmod(filename, 0o400)

# Print the name of the file
print(f"The file created is: {filename}")