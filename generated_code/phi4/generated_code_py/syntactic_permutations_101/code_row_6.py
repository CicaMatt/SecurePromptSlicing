import os

important_config = "This is some important configuration data."

# Ensure necessary directory exists, if not create it
directory = "config_directory"
os.makedirs(directory, exist_ok=True)

file_path = os.path.join(directory, "important_config.txt")

# Open file with write permissions and ensure any existing content is overwritten
with open(file_path, 'w') as file:
    file.write(important_config)