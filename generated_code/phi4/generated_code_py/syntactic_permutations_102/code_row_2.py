import os
import stat

# Define the filename
filename = 'important_config'

# Open the file with O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH flags
with open(filename, 'w+', 
          os.O_CREAT,
          mode=(stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)) as f:
    # Write the string to the file
    f.write('important_config\n')