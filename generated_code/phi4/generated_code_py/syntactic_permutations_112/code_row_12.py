from flask import Flask, request
import subprocess

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', view_func=func)
        return func
    return decorator

@bind_url('ping')
def ping():
    response = subprocess.run(['ping', '-c', '4', request.host], capture_output=True, text=True)
    result = response.stdout if response.returncode == 0 else f"Error: {response.stderr}"
    return result

if __name__ == '__main__':
    app.run(debug=True)