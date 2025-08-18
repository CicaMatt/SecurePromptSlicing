from functools import wraps
import os
import subprocess
from flask import Flask, request

app = Flask(__name__)

def url_trigger(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*url, *args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

@url_trigger('/ping')
def ping(ip_address):
    result = subprocess.run(['ping', '-c', '4', ip_address], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)


To test this application, run the script and navigate to `http://localhost:5000/ping?ip_address=<IP_ADDRESS>` in your web browser or use a tool like `curl` with `http://localhost:5000/ping?ip_address=<IP_ADDRESS>`, replacing `<IP_ADDRESS>` with the actual IP address you want to ping. Make sure Flask is installed by running `pip install flask`.