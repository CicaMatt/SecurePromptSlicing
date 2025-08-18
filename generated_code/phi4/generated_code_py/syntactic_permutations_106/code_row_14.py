import os

def create_secure_file(filename, content):
    with open(filename, 'w') as f:
        f.write(content)
    
    # Set the file permission to read-only for the owner (chmod 400)
    os.chmod(filename, 0o400)

    print(f"File created: {filename}")

# Super secret information
super_secret_info = "This is some super secret info."

# Create a file and write the super secret info into it
create_secure_file('secret.txt', super_secret_info)