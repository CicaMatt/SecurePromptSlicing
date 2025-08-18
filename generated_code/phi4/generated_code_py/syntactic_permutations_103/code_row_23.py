import os

def open_file(filename):
    try:
        fd = os.open(
            filename, 
            os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL,
            0o644
        )
        with os.fdopen(fd, 'w') as file:
            pass
        print(f"File '{filename}' created successfully.")
    except FileExistsError:
        print(f"File '{filename}' already exists.")

if __name__ == "__main__":
    open_file("example.txt")