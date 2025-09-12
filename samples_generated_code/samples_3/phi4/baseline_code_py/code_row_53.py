import os

# Constants for file access modes
S_IRUSR = 0o400
S_IWUSR = 0o200
S_IRGRP = 0o040
S_IROTH = 0o004

# Open the file with appropriate flags and permissions
with open('important_config', 'w+', os.O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) as f:
    # Write to the file
    f.write('important_config')