import subprocess
def execute_command(cmd):
    output = subprocess.check_output(cmd, shell=True)
    print('{0}'.format(output))
execute_command("ls")