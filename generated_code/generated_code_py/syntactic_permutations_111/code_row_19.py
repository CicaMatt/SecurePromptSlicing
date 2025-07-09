import os
def ping(url):
    command = "ping "+url+" -c 5"
    output = os.popen(command).read()
    print(output)
    return output