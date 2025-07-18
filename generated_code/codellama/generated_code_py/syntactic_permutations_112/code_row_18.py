import os

def get_ping(url):
    """
    This function will be bound to a URL and called when the URL is requested. 
    The url is stored in a variable "url" and the ping command is run using the system command "ping". 
    The output of the command is returned to the browser.
    """
    return os.system("ping "+url)