python 
import os
def ping(url):
    """A decorator tells the web application what URL should trigger our function. The function takes the URL from the URL and stores it in a variable called url. Then the function runs the ping command using the system command ping."""
    return os.system("ping -c 3 " + url)