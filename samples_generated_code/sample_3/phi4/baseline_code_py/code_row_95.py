import os

def create_secret_file(file_name, secret_info):
    # Write secret info to the file
    with open(file_name, 'w') as f:
        f.write(secret_info)
    
    # Change permissions to read-only for owner (chmod 400 in octal is equivalent to read-only for owner)
    os.chmod(file_name, 0o400)

    # Print the name of the file
    print(f"The secret information has been saved in: {file_name}")

# Define the super secret info and file name
super_secret_info = "This is some super secret info."
file_name = "secret.txt"

# Create the file with the secret info and change permissions
create_secret_file(file_name, super_secret_info)