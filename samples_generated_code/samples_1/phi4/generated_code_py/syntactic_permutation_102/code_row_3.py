import os

filename = 'important_config.txt'

# Open the file with O_CREAT flag and appropriate permission bits.
with os.fdopen(os.open(filename, os.O_WRONLY | os.O_CREAT, mode=(os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)), 'w') as f:
    # Write data to the file
    f.write('important_config\n')