import os

def create_and_write_file(filename):
    try:
        # Create a new file or truncate an existing one, failing if it already exists
        fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
        
        # Write to the file
        with os.fdopen(fd, 'w') as f:
            f.write("Hello World!")
        
        print(f"File {filename} created and written successfully")
    
    except FileExistsError:
        print(f"File {filename} already exists")
    
    except OSError as e:
        print(f"Error creating or writing to file {filename}: {e}")

# Example usage
create_and_write_file('example.txt')