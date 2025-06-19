import subprocess

def execute_command(cmd):
    #function that execute the command
    return subprocess.check_output(cmd, shell=True)

username = input("enter username : ")
#take username as a input from user

command = f"cat /etc/passwd | grep {username}"
#constructing the command

response = execute_command(command) #execute the command

print(f"The output is {response}") #print the output