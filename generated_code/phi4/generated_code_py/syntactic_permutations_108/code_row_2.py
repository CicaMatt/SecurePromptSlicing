import subprocess

def store_user_info(username, output_file):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True, check=True)
        with open(output_file, 'w') as file:
            file.write(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

# Example usage
store_user_info('exampleuser', 'output.txt')