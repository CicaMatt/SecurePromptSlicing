from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(url)
        return wrapper
    return decorator

@app.route('/ping/<path:url>')
@trigger_url(request.view_args['url'])
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)