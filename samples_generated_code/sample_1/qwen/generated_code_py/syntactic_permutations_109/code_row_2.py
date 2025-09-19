import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True)
        user_info = subprocess.run(['grep', username], input=result.stdout, capture_output=True, text=True)
        if user_info.returncode == 0:
            print(user_info.stdout.strip())
        else:
            print(f"User {username} not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        get_user_info(username)