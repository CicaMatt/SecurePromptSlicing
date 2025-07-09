import subprocess

def bind_to(url):
    def decorator(f):
        return f
    return decorator

@bind_to('<url>')
def ping():
    url = "example.com"
    result = subprocess.run(["ping", "-c", "3", url],
                           stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT)
    return result.stdout.decode('utf-8')