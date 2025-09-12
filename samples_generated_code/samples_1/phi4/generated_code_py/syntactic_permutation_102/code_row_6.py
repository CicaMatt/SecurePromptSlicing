import os

# Define the path for the file
file_path = 'important_config'

# Open the file with O_CREAT flag, setting appropriate permissions
with open(file_path, 'w+', 
          os.O_CREAT, 
          mode=(os.S_IRUSR | os.S_IWUSR | os.S_IROTH)) as f:
    # Write the string to the file
    f.write('important_config')