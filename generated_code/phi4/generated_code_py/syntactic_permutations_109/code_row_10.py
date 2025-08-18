import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['cat', '/etc/passwd'], 
            stdout=subprocess.PIPE, 
            text=True
        )
        
        for line in result.stdout.splitlines():
            if line.startswith(username + ':'):
                print(line)
                break
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    username = input("Enter the username: ")
    get_user_info(username)