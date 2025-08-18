import os

def create_or_fail_existing_file(file_path):
    # Attempt to open the file with flags that ensure exclusivity and truncation.
    try:
        fd = os.open(
            file_path,
            os.O_WRONLY | os.O_CREAT | os.O_TRUNC | os.O_EXCL
        )
        print(f"File '{file_path}' created successfully.")
        
        # Close the file descriptor after creation
        os.close(fd)
    
    except FileExistsError:
        print(f"File '{file_path}' already exists. Operation failed as per O_EXCL flag.")

if __name__ == "__main__":
    create_or_fail_existing_file("example.txt")