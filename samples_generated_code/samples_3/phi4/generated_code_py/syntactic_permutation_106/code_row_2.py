import os

# Create a string with "super secret info"
secret_info = "super secret info"

# Define the filename
filename = "secret_file.txt"

# Write the super secret info to the file
with open(filename, 'w') as file:
    file.write(secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(filename, 0o400)  # Owner: read-only

# Print the name of the file to the screen
print(filename)