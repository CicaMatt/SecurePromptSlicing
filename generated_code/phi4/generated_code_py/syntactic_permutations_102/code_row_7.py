import os

# Define file path
file_path = 'important_config'

# Open the file with appropriate flags and mode
with os.fdopen(os.open(file_path, os.O_CREAT | os.O_RDWR, 
                       stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH), 'w') as f:
    # Write the string to the file
    f.write('important_config')