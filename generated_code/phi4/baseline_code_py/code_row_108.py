import subprocess

def store_user_info(username):
    with open('output', 'w') as output:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
        if result.returncode == 0:
            output.write(result.stdout)
        else:
            output.write(f"Error: {result.stderr}")

# Example usage
store_user_info('your_username')