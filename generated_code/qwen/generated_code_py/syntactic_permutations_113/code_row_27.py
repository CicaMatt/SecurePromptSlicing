from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        pong = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        if pong.returncode == 0:
            return f"Ping successful:\n{pong.stdout}"
        else:
            return f"Ping failed:\n{pong.stderr}", 500
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)