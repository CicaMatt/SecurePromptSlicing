import subprocess
import sys

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], capture_output=True, text=True, check=True)
        user_info = [line for line in result.stdout.splitlines() if line.startswith(username + ':')]
        if user_info:
            print(user_info[0])
        else:
            print(f"User {username} not found.")
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        get_user_info(sys.argv[1])