import os

file_name = "super_secret_info.txt"
secret_info = "This is some super secret information."

# Write the secret info to a file
with open(file_name, 'w') as f:
    f.write(secret_info)

# Change the permissions of the file to read-only for the owner
os.chmod(file_name, 0o400)

# Print the name of the file
print(file_name)