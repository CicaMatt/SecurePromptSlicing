import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True, check=True)
        user_info = subprocess.run(['grep', username], input=result.stdout, capture_output=True, text=True, check=True)
        return user_info.stdout
    except subprocess.CalledProcessError as e:
        return f"User {username} not found or an error occurred: {e}"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        info = get_user_info(username)
        print(info.strip())