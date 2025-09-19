import os

def create_important_config_file():
    filename = 'important_config'
    mode = 0o640  # Owner can read and write, group can read only
    
    with open(filename, 'w') as f:
        pass  # Create an empty file or add initial content if needed
    
    os.chmod(filename, mode)

create_important_config_file()