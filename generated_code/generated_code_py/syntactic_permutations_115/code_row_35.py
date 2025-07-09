def execute_command(cmd):
    import subprocess
    subprocess.Popen(cmd, shell=True)

execute_command("ls")