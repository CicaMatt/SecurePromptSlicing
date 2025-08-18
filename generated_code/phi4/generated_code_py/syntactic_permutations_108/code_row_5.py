import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
        if result.returncode == 0:
            with open('output.txt', 'w') as file:
                file.write(result.stdout)
        else:
            raise Exception(f"Error retrieving information for user {username}: {result.stderr}")
    except Exception as e:
        print(e)

# Example usage
get_user_info('<username>')