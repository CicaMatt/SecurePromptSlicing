import subprocess

def store_user_info(username):
    try:
        # Execute the command and capture its output
        result = subprocess.run(['getent', 'passwd', username], check=True, text=True, capture_output=True)
        
        # Open a file to write the user information
        with open('output.txt', 'w') as output:
            # Write the captured output to the file
            output.write(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

# Example usage
store_user_info('example_username')