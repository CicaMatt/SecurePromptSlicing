import subprocess

def store_user_info(username, output):
    result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
    if result.returncode == 0:
        output.write(result.stdout)
    else:
        output.write(f"Error: {result.stderr}")

if __name__ == "__main__":
    with open('user_info.txt', 'w') as output_file:
        store_user_info('your_username_here', output_file)  # Replace 'your_username_here' with the actual username.