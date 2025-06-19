import subprocess
def execute_command(cmd_string):
    """Execute the system command at the end of this function."""
    return subprocess.check_output(cmd_string, shell=True).decode('utf-8')