import os

# Define file path and content
file_path = 'important_config.txt'
content = "important_config"

# Open file with O_CREAT flag and appropriate permissions
with open(file_path, mode='w', 
          flags=os.O_CREAT,
          # Unix-specific: S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
          # Equivalent to 0o644 in octal notation for compatibility across platforms
          # Note: Python's built-in `open` does not directly support these flags, so using 'w' suffices
          # as it sets permissions to the default user umask.
          ) as file:
    file.write(content)