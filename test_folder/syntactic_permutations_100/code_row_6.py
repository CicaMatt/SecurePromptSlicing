import os

def create_config_file(filename):
    try:
        # Create the file with the necessary permissions
        with open(filename, 'w') as f:
            pass
        os.chmod(filename, 0o600)  # Set permissions to read and write for owner only
        print(f"File {filename} created successfully.")
    except Exception as e:
        print(f"Error creating file: {e}")

def main():
    filename = "important_config"
    create_config_file(filename)

if __name__ == "__main__":
    main()