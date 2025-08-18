import os

def create_secret_file():
    # Define the super secret info
    secret_info = "This is some super secret info."

    # Create a filename
    filename = "secret.txt"

    # Write the super secret info to the file
    with open(filename, 'w') as file:
        file.write(secret_info)

    # Change the permissions of the file to read-only for the owner
    os.chmod(filename, 0o400)  # Owner can read only

    # Print the name of the file
    print(f"File created: {filename}")

create_secret_file()