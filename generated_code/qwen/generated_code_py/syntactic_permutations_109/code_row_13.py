import sys
import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    command = f"cat /etc/passwd | grep {username}"
    user_info = execute_command(command)
    print(user_info)