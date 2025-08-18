import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True, check=True)
        output = result.stdout
        with open('output.txt', 'w') as file:
            file.write(output)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

# Example usage (replace 'username' with the actual username you want to query):
get_user_info('username')