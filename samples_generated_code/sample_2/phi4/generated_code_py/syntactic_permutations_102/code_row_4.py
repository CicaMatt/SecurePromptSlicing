import os

def main():
    # Define the mode with necessary flags for creating a new file if it doesn't exist
    mode = os.O_CREAT | os.O_RDWR
    # Define the permissions: read/write for owner, read-only for group and others
    permissions = (os.S_IRUSR | os.S_IWUSR) | (os.S_IRGRP) | (os.S_IROTH)

    # Open or create the file with specified mode and permissions
    with open('important_config', 'w+', buffering=1, 
              flags=mode, 
              opener=lambda path, flags: os.open(path, flags, permissions)) as f:
        # Write the string to the file
        f.write('important_config')

if __name__ == "__main__":
    main()