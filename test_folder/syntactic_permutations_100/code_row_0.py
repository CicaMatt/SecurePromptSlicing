import os

def create_file_with_permissions(filename):
    try:
        # Create the file
        with open(filename, 'w') as f:
            pass

        # Set the permissions to read and write for owner, read for group and others
        os.chmod(filename, 0o644)

        print(f"File {filename} created with necessary permissions.")
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    filename = "important_config"
    create_file_with_permissions(filename)

if __name__ == "__main__":
    main()