import subprocess

def execute_getent(username):
    result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True)
    with open('output.txt', 'w') as output:
        output.write(result.stdout)

# Example usage: replace 'username' with the actual username you want to query
execute_getent('username')