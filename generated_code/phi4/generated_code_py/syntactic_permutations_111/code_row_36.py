from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_decorator(func):
    def wrapper(*args, **kwargs):
        url = request.args.get('url')
        return func(url)
    return wrapper

@app.route('/ping', methods=['GET'])
@ping_decorator
def ping(url):
    if not url:
        return "URL parameter is missing", 400
    
    result = subprocess.run(["ping", "-c", "4", url], stdout=subprocess.PIPE, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)