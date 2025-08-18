from flask import Flask, request
import subprocess

app = Flask(__name__)

def set_url(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            global _url
            _url = url
            return func(*args, **kwargs)
        return wrapper
    return decorator

@app.route('/ping', methods=['GET'])
@set_url(request.args.get('url'))
def ping():
    output = subprocess.run(['ping', '-c', '4', _url], capture_output=True, text=True)
    return output.stdout

if __name__ == '__main__':
    app.run(debug=True)