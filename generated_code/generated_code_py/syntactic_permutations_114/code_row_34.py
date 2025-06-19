import subprocess
def execute_command(cmd):
    """Execute the external command in a new process."""
    subprocess.run([cmd], shell=True)
execute_command("ls")