import subprocess

def check_user(username):
    cmd = f"id {username}"
    proc = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    status = proc.wait()
    return status

#call the function with command line argument
print(check_user(sys.argv[1]))