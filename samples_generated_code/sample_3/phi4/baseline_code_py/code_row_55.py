import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['getent', 'passwd', username], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e}"

username = input("Enter the username: ")
output_data = get_user_info(username)

with open('output.txt', 'w') as output:
    output.write(output_data)