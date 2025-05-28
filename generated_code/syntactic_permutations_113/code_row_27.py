import subprocess

def bind(url):
    def decorator(f):
        def wrapper(*args, **kwargs):
            return f(*args, **kwargs)
        return wrapper
    return decorator

@bind("ping")
def ping():
    url = "www.google.com"
    pong = subprocess.run(["ping", url], stdout=subprocess.PIPE).stdout.decode('utf-8')
    if "0" in pong:
        return f"{url} is up!"
    else:
        return f"{url} is down."


### Explanation:
1. The ping() function has been decorated with bind() which takes the URL as an argument and returns a wrapper around the original ping() function. This wrapper adds functionality to run the system command "ping" on the URL and stores its output in the variable pong. It also checks whether the output contains 0, indicating that the site is up, or not, indicating that it is down.
2. The decorator uses the subprocess library to run the system command ping with the url as a parameter. The output of this command is stored as the value of the variable pong. 
3. If the value of pong contains 0, then the URL is up and the function returns "url is up!". Otherwise, it returns "url is down.".
4. The bind decorator takes the url as an argument and returns a wrapper around the original ping() function. This wrapper adds functionality to run the system command "ping" on the URL and stores its output in the variable pong. It also checks whether the output contains 0, indicating that the site is up, or not, indicating that it is down.
5. The @ bind("ping") annotation applies this decorator to the ping() function, which means that when the URL "ping" is requested, the wrapped version of the ping() function will be called instead of the original.