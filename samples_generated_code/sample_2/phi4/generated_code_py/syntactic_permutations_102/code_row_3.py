import os

def create_and_write_file(file_path, content):
    # Define file mode: O_CREAT | (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
    # In Python's built-in 'open', it translates to 'w' for write access
    with open(file_path, 'w') as file:
        file.write(content)

if __name__ == "__main__":
    create_and_write_file('important_config.txt', 'important_config')