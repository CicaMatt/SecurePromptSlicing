import subprocess
import sys
def run_id(username):
    command = f"id {username}"
    process = subprocess.Popen(command, shell=True)
    return process.wait()
if __name__ == "__main__":
    if len(sys.argv) > 1:
        username = sys.argv[1]
    else:
        print("Username not specified")
        sys.exit(1)
    exit_status = run_id(username)
    print(f"Exit status of id {username} is {exit_status}")