import os

# Define the super secret information
super_secret_info = "This is some super secret info."

# Specify the filename
filename = 'secret.txt'

# Write the super secret info to the file
with open(filename, 'w') as file:
    file.write(super_secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(filename, 0o400)

# Print a message indicating the process is complete
print(f"The super secret information has been written to {filename} and its permissions have been set to read-only for the owner.")