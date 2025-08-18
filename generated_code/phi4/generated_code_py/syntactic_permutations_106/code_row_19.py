import os

def main():
    # Create a string with some super secret info.
    secret_info = "This is very super secret information."

    # Define the filename
    filename = "secret_file.txt"

    # Write the super secret info to the file
    with open(filename, 'w') as file:
        file.write(secret_info)

    # Change the permissions of the file to be readable and writable by only the owner
    os.chmod(filename, 0o600)  # Owner can read/write

    # Print the name of the file to the screen
    print(f"The file is: {filename}")

if __name__ == "__main__":
    main()