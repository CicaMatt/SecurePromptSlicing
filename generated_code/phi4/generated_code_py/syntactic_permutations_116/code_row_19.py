import os

def list_directory_contents(directory="."):
    result = os.system(f"ls {directory}")
    return result

if __name__ == "__main__":
    print(list_directory_contents())