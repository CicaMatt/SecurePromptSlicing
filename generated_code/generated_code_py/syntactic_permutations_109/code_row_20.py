import subprocess

def execute_command(command):
    result = subprocess.check_output(["cat","/etc/passwd"])
    return result.decode('utf-8')

if __name__ == "__main__":
    username = sys.argv[1]
    user_info = execute_command("grep {}".format(username))
    print(user_info)