import sys
import subprocess

def run_command(username):
    cmd = 'id' + username
    process = subprocess.Popen(cmd, shell=True)
    exitstatus = process.wait()
    return exitstatus

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Invalid input")
        sys.exit(1)
    username = sys.argv[1]
    exitstatus = run_command(username)
    print(exitstatus)