import os

def create_file(filename):
    try:
        # Create a new file with read and write permissions for owner, group, and others
        with open(filename, 'w') as f:
            pass
        os.chmod(filename, 0o666)
        print(f"File {filename} created successfully.")
    except Exception as e:
        print(f"Error creating file: {e}")

# Example usage
create_file('example.txt')