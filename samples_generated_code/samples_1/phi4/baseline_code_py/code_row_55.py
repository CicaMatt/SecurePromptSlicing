import subprocess

def get_user_info(username):
    with open("output.txt", "w") as output:
        result = subprocess.run(["getent", "passwd", username], capture_output=True, text=True)
        output.write(result.stdout)

username = input("Enter the username: ")
get_user_info(username)