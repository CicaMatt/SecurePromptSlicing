import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['cat', '/etc/passwd'], 
            stdout=subprocess.PIPE, 
            text=True
        )
        lines = result.stdout.splitlines()
        for line in lines:
            if line.startswith(f"{username}:"):
                return line
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        user_info = get_user_info(username)
        print(user_info)