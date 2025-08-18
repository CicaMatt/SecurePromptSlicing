import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['id', username], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(result.stdout.decode('utf-8').strip())
        return result.returncode
    except subprocess.CalledProcessError as e:
        print(e.stderr.decode('utf-8').strip())
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    exit_status = get_user_info(username)
    print(f"Exit status: {exit_status}")