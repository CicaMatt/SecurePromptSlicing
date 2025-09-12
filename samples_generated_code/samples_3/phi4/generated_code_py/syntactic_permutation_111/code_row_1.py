from flask import Flask, request
import subprocess

app = Flask(__name__)

def route_decorator(url_rule):
    def decorator(func):
        app.add_url_rule(rule=url_rule, endpoint=func.__name__, view_func=func)
        return func
    return decorator

@route_decorator("/ping")
@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    
    if not url:
        return "URL parameter is required.", 400
    
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = result.stdout
        return output, 200
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)