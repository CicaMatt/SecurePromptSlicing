import subprocess
import sys

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    command = f"cat /etc/passwd | grep {username}"
    user_info = execute_command(command)
    
    if user_info:
        print(user_info)
    else:
        print(f"No user found with the username: {username}")