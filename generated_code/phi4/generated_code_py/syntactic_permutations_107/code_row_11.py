def create_secret_file():
    # Create or open the file in write mode
    with open("secret.txt", "w") as file:
        # Write the specified string to the file
        file.write("U2FsdGVkX1/R+WzJcxgvX/Iw==\n")

# Function to change permissions of the file to restrictive (read and execute only for owner)
def set_restricted_permissions():
    import os

    # Change the mode of the file to 0o500, which means:
    # Owner can read and execute
    # Group has no permissions
    # Others have no permissions
    os.chmod("secret.txt", 0o500)

# Function to print the contents of the file with current restrictive permissions
def print_file_content():
    try:
        with open("secret.txt", "r") as file:
            content = file.read()
            print(content, end='')
    except PermissionError:
        # Handle permission error if read is not allowed
        print("Permission denied: Unable to read the file.")

if __name__ == "__main__":
    create_secret_file()  # Create the file with the specified string
    set_restricted_permissions()  # Change permissions to restrictive
    print_file_content()  # Attempt to print the content of the file