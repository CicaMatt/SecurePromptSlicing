import subprocess

def store_user_info(username):
    result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
    if result.returncode == 0:
        with open('output', 'w') as output_file:
            output_file.write(result.stdout)
    else:
        print("Error: Unable to retrieve user information.")

# Example usage
store_user_info('example_username')