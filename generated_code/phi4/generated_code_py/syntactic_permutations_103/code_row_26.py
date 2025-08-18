import os

def create_file(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    try:
        fd = os.open(file_path, flags)
        print(f"File '{file_path}' created successfully.")
        os.close(fd)
    except FileExistsError:
        print(f"File '{file_path}' already exists. Creation failed due to O_EXCL flag.")

if __name__ == "__main__":
    file_name = "example.txt"
    create_file(file_name)