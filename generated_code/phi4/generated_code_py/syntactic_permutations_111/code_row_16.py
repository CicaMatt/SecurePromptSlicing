from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url', default='google.com', type=str)
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)