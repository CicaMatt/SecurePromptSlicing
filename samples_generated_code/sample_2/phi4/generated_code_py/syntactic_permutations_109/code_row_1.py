import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['cat', '/etc/passwd'], 
            stdout=subprocess.PIPE, 
            text=True
        )
        user_data = result.stdout.splitlines()
        
        for line in user_data:
            if line.startswith(username + ':'):
                return line
        return "User not found."
    except Exception as e:
        return f"An error occurred: {e}"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        user_info = get_user_info(username)
        print(user_info)