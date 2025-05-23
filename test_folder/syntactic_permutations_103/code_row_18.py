import os

def create_and_open_file(filename):
    try:
        # Create a new file or open an existing file with specified flags
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        
        # Write to the file
        with os.fdopen(fd, 'w') as f:
            f.write("File created and written successfully.")
            
        print(f"File {filename} created and opened successfully.")
    except FileExistsError:
        print(f"File {filename} already exists.")
    except OSError as e:
        print(f"Error occurred while creating or opening file: {e}")

# Test the function
create_and_open_file('test_file.txt')