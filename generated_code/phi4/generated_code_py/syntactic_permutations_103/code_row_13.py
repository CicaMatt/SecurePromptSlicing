import os

def safe_create_file(file_path):
    try:
        # Open file with flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
        fd = os.open(
            file_path,
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
        )
        print(f"File '{file_path}' created successfully.")
    except FileExistsError:
        print(f"File '{file_path}' already exists. Creation failed.")

# Example usage
safe_create_file("example.txt")