from flask import Flask, redirect
import os

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @app.route(url)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

@bind_to_url('/run-command')
def run_command():
    # Example system command: list directory contents (os.system is used here for demonstration purposes; use subprocess for better security and flexibility in production code)
    os.system('ls -l')
    return "Command executed"

if __name__ == '__main__':
    app.run(debug=True)