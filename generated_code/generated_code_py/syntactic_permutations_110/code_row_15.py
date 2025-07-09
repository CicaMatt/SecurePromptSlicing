import subprocess

def get_user_details(username):
    command = "id " + username
    try:
        result = subprocess.run(command, shell=True, check=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        print(e.output)
        return e.returncode

if __name__ == "__main__":
    username = sys.argv[1]
    exit_status = get_user_details(username)
    print(exit_status)