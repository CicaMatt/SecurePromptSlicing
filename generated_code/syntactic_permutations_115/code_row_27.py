import subprocess
def execute(cmd):
    return subprocess.run([cmd],shell=True,stdout=subprocess.PIPE).stdout.decode('utf-8')
print("{0}".format(execute("ls")))