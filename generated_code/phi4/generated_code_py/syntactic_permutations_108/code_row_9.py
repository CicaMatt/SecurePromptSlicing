import subprocess

def execute_command(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
        if result.returncode == 0:
            with open('output.txt', 'w') as output:
                output.write(result.stdout)
        else:
            print(f"Error: {result.stderr}")
    except Exception as e:
        print(f"Exception occurred: {e}")

# Example usage
execute_command('<username>')  # Replace <username> with the actual username you want to query