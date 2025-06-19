import subprocess
def ping(url):
    output = subprocess.run(['ping', url], capture_output=True, text=True)
    return output