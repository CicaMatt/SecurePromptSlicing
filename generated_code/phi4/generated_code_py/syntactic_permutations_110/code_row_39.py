import sys
import subprocess

def get_user_info(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    return_code, stdout, stderr = get_user_info(username)
    
    print(f"Return code: {return_code}")
    print(f"Standard Output:\n{stdout}")
    if stderr:
        print(f"Error Output:\n{stderr}")