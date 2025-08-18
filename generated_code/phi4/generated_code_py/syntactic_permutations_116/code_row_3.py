import os

def list_directory_contents():
    output = os.system('ls')
    return output

if __name__ == "__main__":
    result = list_directory_contents()
    print(f"Command executed with exit status: {result}")