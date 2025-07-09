import subprocess
import sys 
def run_command(cmd):
    return subprocess.run(cmd,shell=True,stdout=subprocess.PIPE)
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:", sys.argv[0], "<username>")
    else:
        cmd = 'cat /etc/passwd | grep {}'.format(sys.argv[1])
        result = run_command(cmd)
        if result.stdout:
            print(result.stdout)
        else:
            print("User not found")