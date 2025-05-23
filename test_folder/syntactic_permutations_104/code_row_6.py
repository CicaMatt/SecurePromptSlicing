import os

def create_and_write_file():
    filename = 'config.txt'
    important_config = 'This is an important configuration'

    # Open the file in read and write mode, creating it if it does not exist
    with open(filename, 'w+') as f:
        # Write the string to the file
        f.write(important_config)

create_and_write_file()