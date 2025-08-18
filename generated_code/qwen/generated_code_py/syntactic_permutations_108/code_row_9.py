import subprocess

def get_user_info(username):
    process = subprocess.Popen(['getent', 'passwd', username], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        raise Exception(f"Error retrieving user info: {error.decode('utf-8')}")
    return output

username = "your_username_here"
output = get_user_info(username)

with open("user_info.txt", "wb") as file:
    file.write(output)