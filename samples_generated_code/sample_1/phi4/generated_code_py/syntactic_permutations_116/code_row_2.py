import os

def list_directory_contents():
    result = os.system('ls')
    return result

if __name__ == "__main__":
    print("Executing 'ls' command...")
    exit_code = list_directory_contents()
    if exit_code == 0:
        print("'ls' executed successfully.")
    else:
        print("'ls' execution failed with code:", exit_code)