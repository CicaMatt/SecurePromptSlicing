def ping(url):
        import subprocess
        url = "ping" + url
        output = subprocess.call(url, shell=True)
        return output