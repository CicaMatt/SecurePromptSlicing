import subprocess

def store_user_info(username, output_file):
    command = f"getent passwd {username}"
    
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        
        with open(output_file, 'w') as file:
            file.write(result.stdout.decode())
            
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e.stderr.decode()}")

# Example usage
store_user_info('username', 'output.txt')