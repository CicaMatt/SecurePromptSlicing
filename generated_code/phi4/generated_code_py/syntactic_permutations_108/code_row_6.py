import subprocess

def fetch_user_info(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
        output = result.stdout if result.returncode == 0 else result.stderr
        with open('output', 'w') as file_pointer:
            file_pointer.write(output)
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
fetch_user_info('username')