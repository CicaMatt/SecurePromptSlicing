from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@bind_to_url('ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e}", 500

if __name__ == '__main__':
    app.run(debug=True)