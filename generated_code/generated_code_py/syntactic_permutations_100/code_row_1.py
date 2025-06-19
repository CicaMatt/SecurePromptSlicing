import os
import stat

def create_file():
    try:
        with open("important_config", "x") as f:
            os.chmod("important_config", stat.S_IRUSR)
            return True
    except FileExistsError:
        return False