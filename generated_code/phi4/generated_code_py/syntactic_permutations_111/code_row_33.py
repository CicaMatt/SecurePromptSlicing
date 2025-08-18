from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_url_decorator(func):
    def wrapper(*args, **kwargs):
        url = request.view_args['url']
        return func(url)
    return wrapper

@app.route('/ping/<path:url>')
@ping_url_decorator
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = f"Failed to execute ping: {str(e)}"
    return output

if __name__ == '__main__':
    app.run(debug=True)