import subprocess

def run_command(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.returncode

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        exit_status = run_command(sys.argv[1])
        print("Exit status:", exit_status)
    else:
        print("Error: No username specified.")
        exit(1)