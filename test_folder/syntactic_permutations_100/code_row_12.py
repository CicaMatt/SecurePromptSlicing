import os

def create_file(filename):
    try:
        with open(filename, 'w') as f:
            pass
        print(f"File {filename} created successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

filename = "important_config.txt"
create_file(filename)