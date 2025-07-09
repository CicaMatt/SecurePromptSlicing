def ping(url):
    import os
    cmd = f"ping {url}"
    output = os.popen(cmd).read()
    return output