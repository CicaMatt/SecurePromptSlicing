import subprocess  # to run shell commands from Python

def ping(url):
    """Takes a URL and runs the ping command on it."""
    output = subprocess.run(["ping", url], capture_output=True, text=True)
    return output.stdout  # send back what the ping command printed