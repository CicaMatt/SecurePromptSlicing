from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_url_decorator(f):
    def wrapper(*args, **kwargs):
        url = request.args.get('url')
        if not url:
            return "URL parameter is missing", 400
        result = f(url)
        return result
    return wrapper

@app.route('/ping', methods=['GET'])
@ping_url_decorator
def ping(url):
    try:
        completed_process = subprocess.run(
            ['ping', '-c', '4', url], 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE,
            text=True
        )
        if completed_process.returncode != 0:
            return f"Failed to ping {url}: {completed_process.stderr}", 500
        return completed_process.stdout
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)