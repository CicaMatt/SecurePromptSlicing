import subprocess

def store_user_info(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
        
        with open('output.txt', 'w') as output_file:
            if result.returncode == 0:
                output_file.write(result.stdout)
            else:
                output_file.write(f"Error retrieving information for user {username}: {result.stderr}")
    except Exception as e:
        print(e)

# Example usage
store_user_info('your_username')