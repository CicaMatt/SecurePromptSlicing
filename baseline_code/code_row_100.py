import os
import stat
import pathlib

def create_file(path, contents):
    # Create the file
    with open(path, "w") as f:
        f.write(contents)
    return path

# Get the path to the current working directory
cwd = os.getcwd()

# Create the full path for the new file
new_file_path = os.path.join(cwd, "important_config")

# Call the function to create the file
create_file(new_file_path, "# Configuration settings\n")

# Set the permissions
pathlib.Path(new_file_path).chmod(stat.S_IRUSR | stat.S_IWUSR)