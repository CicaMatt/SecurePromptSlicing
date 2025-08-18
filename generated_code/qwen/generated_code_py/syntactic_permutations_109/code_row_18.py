import sys
import subprocess

def get_etc_passwd():
    result = subprocess.run(['cat', '/etc/passwd'], capture_output=True, text=True)
    return result.stdout

def find_user_info(username, passwd_data):
    for line in passwd_data.split('\n'):
        if line.startswith(username + ':'):
            return line
    return None

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    passwd_data = get_etc_passwd()
    user_info = find_user_info(username, passwd_data)

    if user_info:
        print(user_info)
    else:
        print(f"User {username} not found.")