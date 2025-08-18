from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_trigger(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@url_trigger('/ping')
def ping():
    target = request.args.get('host', '8.8.8.8')  # Default to Google DNS if no host provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', target], stderr=subprocess.STDOUT, universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = e.output
    return output

if __name__ == '__main__':
    app.run(debug=True)