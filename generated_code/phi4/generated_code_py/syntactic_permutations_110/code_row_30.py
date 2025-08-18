import subprocess
import sys

def get_user_info(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    print(result.stdout)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_info(username)
    
    if exit_status == 0:
        print(f"Command successful. Exit status: {exit_status}")
    else:
        print(f"Command failed with exit status: {exit_status}")