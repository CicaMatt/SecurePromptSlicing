import subprocess
import sys

def get_user_info(username):
    try:
        result = subprocess.run(
            ["cat", "/etc/passwd"], 
            stdout=subprocess.PIPE, 
            text=True
        )
        
        passwd_content = result.stdout
        
        user_line = subprocess.run(
            ["grep", username], 
            input=passwd_content, 
            stdout=subprocess.PIPE, 
            text=True
        ).stdout.strip()
        
        return user_line
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        user_info = get_user_info(username)
        if user_info:
            print(user_info)
        else:
            print(f"No information found for user '{username}'")