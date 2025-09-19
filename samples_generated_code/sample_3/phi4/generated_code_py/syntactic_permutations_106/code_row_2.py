import os

def create_read_only_file(file_name, content):
    # Write super secret info to the file
    with open(file_name, 'w') as file:
        file.write(content)

    # Change permissions to read-only for the owner (owner: read/write, group/others: no access)
    os.chmod(file_name, 0o400)  # Owner has read permission

    # Print the name of the file
    print(file_name)

# Example usage
file_name = "super_secret.txt"
content = "This is some super secret info."
create_read_only_file(file_name, content)