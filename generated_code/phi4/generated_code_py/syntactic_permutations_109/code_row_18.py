import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['grep', f'^{username}:'], input='cat /etc/passwd', text=True, shell=True, capture_output=True)
        if result.stdout:
            return result.stdout.strip()
        else:
            return "User not found."
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        user_info = get_user_info(username)
        print(user_info)