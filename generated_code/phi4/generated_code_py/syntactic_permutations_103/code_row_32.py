import os

# Create a new file or open an existing one, truncating its contents if it exists
file_path = 'example.txt'
os_flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY

try:
    with os.fdopen(os.open(file_path, os_flags), 'w') as file:
        # Write content to the file
        file.write("This is some example text.")
except OSError as e:
    print(f"An error occurred: {e}")