import os

def list_directory_contents():
    command = "ls"
    result = os.system(command)
    return result

if __name__ == "__main__":
    output = list_directory_contents()
    print(f"Command executed with exit code: {output}")