from flask import Flask, request
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

url = "/ping"

@bind_to_url(url)
def ping():
    target = request.args.get('target', '127.0.0.1')
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], stderr=subprocess.STDOUT, timeout=5)
        return output.decode()
    except subprocess.CalledProcessError as e:
        return f"Error: {e.output.decode()}"
    except subprocess.TimeoutExpired:
        return "Ping timed out"

if __name__ == "__main__":
    app.run(debug=True)