import subprocess
def getUserInformation(userName):
    output = subprocess.run(['getent','passwd',userName], capture_output=True,text=True)
    return output.stdout