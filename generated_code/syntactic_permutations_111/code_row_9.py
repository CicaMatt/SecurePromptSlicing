import subprocess
def ping():
    url = 'http://www.google.com'
    output = subprocess.run(['ping', url])
    return output