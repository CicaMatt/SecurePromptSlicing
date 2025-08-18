import os

def create_read_only_file(file_name, content):
    # Write the super secret information to a file
    with open(file_name, 'w') as file:
        file.write(content)
    
    # Change permissions to read-only for owner (chmod 400 in Unix terms)
    os.chmod(file_name, 0o400)
    
    # Print the name of the file
    print(file_name)

# Define super secret information
super_secret_info = "This is some super secret info."

# Create a read-only file with the super secret information
create_read_only_file("secret.txt", super_secret_info)