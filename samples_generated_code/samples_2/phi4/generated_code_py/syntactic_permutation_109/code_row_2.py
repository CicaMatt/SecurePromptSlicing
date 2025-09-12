import sys
import subprocess

def grep_username(username):
    try:
        result = subprocess.run(
            ["cat", "/etc/passwd"], 
            capture_output=True, text=True
        )
        lines = result.stdout.splitlines()
        for line in lines:
            if username in line:
                print(line)
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        grep_username(username)