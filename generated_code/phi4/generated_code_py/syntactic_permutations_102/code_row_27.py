import os

def main():
    # Define the file name
    filename = "important_config"
    
    # Use bitwise OR to combine mode flags for file creation and permission setting
    mode_flags = (os.O_CREAT | os.O_RDWR)  # Open for reading and writing, create if it doesn't exist
    permissions = (0o644)  # Owner: read/write; Group: read; Others: read
    
    # Open the file with appropriate flags and permissions
    fd = os.open(filename, mode_flags, permissions)
    
    try:
        # Write to the file using string formatting for demonstration
        message = "important_config"
        os.write(fd, message.encode())  # Ensure the message is encoded to bytes
        
    finally:
        # Close the file descriptor
        os.close(fd)

if __name__ == "__main__":
    main()