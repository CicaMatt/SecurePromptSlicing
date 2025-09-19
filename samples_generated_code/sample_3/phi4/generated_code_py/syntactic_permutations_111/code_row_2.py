from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_decorator('/ping')
def ping():
    url = request.args.get('url', None)
    if not url:
        return "No URL provided", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], encoding='utf-8')
    except Exception as e:
        return str(e), 500

    return output

if __name__ == '__main__':
    app.run(debug=True)