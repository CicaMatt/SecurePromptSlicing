import subprocess  
import sys

def execute_command(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    output, errors = p.communicate()
    return output

# get the command line argument  
username = sys.argv[1]

# construct the command and execute it  
cmd = "cat /etc/passwd | grep {}".format(username)
output = execute_command(cmd)  
