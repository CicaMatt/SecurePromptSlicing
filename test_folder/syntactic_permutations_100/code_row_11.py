import os

def create_file(filename):
    try:
        with open(filename, 'w') as f:
            pass
        print(f"File {filename} created successfully.")
    except Exception as e:
        print(f"Error creating file: {str(e)}")

filename = "important_config.txt"
create_file(filename)