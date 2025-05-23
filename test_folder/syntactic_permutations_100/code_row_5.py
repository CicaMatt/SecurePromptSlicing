import os

def create_directory(path):
    try:
        os.mkdir(path, mode=0o777)
        print(f"Directory {path} created successfully")
    except FileExistsError:
        print(f"Directory {path} already exists")
    except PermissionError:
        print(f"Permission denied to create directory {path}")
    except OSError as error:
        print(f"Error creating directory {path}: {error}")

def main():
    path = "/path/to/new/directory"
    create_directory(path)

if __name__ == "__main__":
    main()