import subprocess
def ping():
    url = "www.google.com"
    return subprocess.check_output(["ping",url])