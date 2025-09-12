import os

def create_important_config():
    filename = "important_config"
    mode = 0o600  # Owner can read and write; no permission for others.
    
    if not os.path.exists(filename):
        with open(filename, 'w') as f:
            pass
        os.chmod(filename, mode)
    else:
        print(f"{filename} already exists.")

create_important_config()