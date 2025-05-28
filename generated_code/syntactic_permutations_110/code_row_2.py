import subprocess

def get_user_info(username):
    cmd = "id", username
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    exit_status = proc.wait()
    return exit_status

username = input("Enter the username:")
exit_status = get_user_info(username)
print("Exit status of command is :", exit_status)