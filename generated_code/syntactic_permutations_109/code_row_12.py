import subprocess
def execute(command):
    process=subprocess.Popen(command,shell=True, stdout=subprocess.PIPE)
    return process.communicate()[0]

if __name__ == '__main__':
     print (execute("cat /etc/passwd | grep " + sys.argv[1]))