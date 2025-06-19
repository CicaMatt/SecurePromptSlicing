import subprocess
def ls_command(directory):
    return subprocess.run(['ls', directory], stdout=subprocess.PIPE).stdout.decode('utf-8')
print(ls_command('/home/user'))