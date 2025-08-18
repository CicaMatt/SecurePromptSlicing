from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_decorator(f):
    def wrapper():
        return f()
    app.add_url_rule('/ping', 'ping', wrapper)
    return wrapper

@url_decorator
def ping():
    target = request.args.get('target', '127.0.0.1')
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], stderr=subprocess.STDOUT, timeout=10)
        output = output.decode()
    except subprocess.CalledProcessError as e:
        output = "Ping failed: " + str(e.output.decode())
    except subprocess.TimeoutExpired:
        output = "Ping timed out"
    return output

if __name__ == '__main__':
    app.run(debug=True)