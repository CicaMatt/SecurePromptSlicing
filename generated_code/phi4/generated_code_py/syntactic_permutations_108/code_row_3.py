import subprocess

def store_user_info(username, output_file_path):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True, check=True)
        with open(output_file_path, 'w') as output_file:
            output_file.write(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

# Example usage
store_user_info('username_to_check', 'output.txt')