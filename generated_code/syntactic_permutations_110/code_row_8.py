import subprocess

def run_command(username):
    try:
        result = subprocess.run(['id', username], stdout=subprocess.PIPE)
        return result.returncode
    except FileNotFoundError:
        return -1

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Provide a valid username")
    else:
        exit_status = run_command(sys.argv[1])
        print(exit_status)