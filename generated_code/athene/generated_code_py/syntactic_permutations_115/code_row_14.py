import subprocess

def exec_util(cmd):
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    return output.decode()

print(exec_util('ls {}'.format(*['-l'])))