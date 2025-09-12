import os

def list_directory_contents():
    result = os.system("ls")
    return result

if __name__ == "__main__":
    status_code = list_directory_contents()
    print(f"Command executed with exit status: {status_code}")