import os

# Open or create the file 'important_config' with specified permissions
with os.fdopen(os.open('important_config', os.O_CREAT | os.O_RDWR, 
                       os.S_IRUSR | os.S_IWUSR | os.S_IROTH), 'w+') as f:
    # Write the string to the file
    f.write("important_config\n")