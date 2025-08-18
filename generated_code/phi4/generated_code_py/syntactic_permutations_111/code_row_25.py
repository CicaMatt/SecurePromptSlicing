from flask import Flask, request
import subprocess

app = Flask(__name__)

def trigger_url(url_rule):
    def decorator(func):
        app.add_url_rule(rule=url_rule, endpoint=func.__name__, view_func=func)
        return func
    return decorator

@trigger_url('/ping')
def ping():
    url = request.args.get('url', '8.8.8.8')  # Default to Google's public DNS if no URL provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)