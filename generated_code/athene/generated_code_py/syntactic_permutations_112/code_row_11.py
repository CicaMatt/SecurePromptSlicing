import os
from flask import Flask, request

app = Flask(__name__)

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@bind_to_url(url='/run_command')
def run_command():
    url = request.url
    os.system("")  # Placeholder for the system command
    return url

if __name__ == '__main__':
    app.run(debug=True)