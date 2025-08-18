import os

# Open the file 'important_config' in read/write mode, creating it if it doesn't exist
with os.fdopen(os.open('important_config', os.O_RDWR | os.O_CREAT, 
                       os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)) as f:
    # Write the string 'important_config' to the file
    f.write('important_config')