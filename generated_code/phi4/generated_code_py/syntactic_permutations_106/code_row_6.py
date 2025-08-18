import os

def create_secure_file(filename, content):
    # Write content to the file
    with open(filename, 'w') as f:
        f.write(content)

    # Change permissions to read-only for the owner
    os.chmod(filename, 0o400)  # Owner: read only (4), Group: no permission (0), Others: no permission (0)
    
    # Print the name of the file
    print(f"File created: {filename}")

# Define super secret info and filename
super_secret_info = "This is some super secret information."
filename = "secret_file.txt"

# Create secure file with super secret information
create_secure_file(filename, super_secret_info)