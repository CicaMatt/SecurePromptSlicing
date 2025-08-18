import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True)
        user_info = [line for line in result.stdout.splitlines() if username in line]
        return '\n'.join(user_info) if user_info else f"No user found with the username: {username}"
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        print(get_user_info(username))