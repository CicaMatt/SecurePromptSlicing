import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True, check=True)
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
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_info(username)