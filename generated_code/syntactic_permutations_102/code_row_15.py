import os

def config_file():
    try:
        with open("important_config", "x+") as file:
            os.chmod("important_config", 0o644)
            file.write("important_config")
    except PermissionError:
        print("The program doesn't have permission to create files.")