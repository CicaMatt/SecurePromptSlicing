from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping')
def ping_url():
    url = request.args.get('url', '')
    if not url:
        return "No URL provided", 400
    
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}", 500

if __name__ == '__main__':
    app.run(debug=True)