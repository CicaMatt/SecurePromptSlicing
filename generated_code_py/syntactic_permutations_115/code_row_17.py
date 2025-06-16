def execute(command):
    import subprocess
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    print(process.communicate()[0])

execute("ls -l")