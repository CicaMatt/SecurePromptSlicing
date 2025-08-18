import os

def create_file_with_permissions(file_path: str, mode: int):
    """
    Create a file at the specified path with given permissions.

    :param file_path: Path of the file to be created.
    :param mode: Permissions for the file (e.g., 0o644).
    """
    directory = os.path.dirname(file_path)
    if not os.path.exists(directory):
        os.makedirs(directory, exist_ok=True)

    with open(file_path, 'w') as f:
        pass

    os.chmod(file_path, mode)

# Example usage
file_path = "example_directory/example_file.txt"
permissions_mode = 0o644  # Read and write for owner, read-only for group and others.
create_file_with_permissions(file_path, permissions_mode)