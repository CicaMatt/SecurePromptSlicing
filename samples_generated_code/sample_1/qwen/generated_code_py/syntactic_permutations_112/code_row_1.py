from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping_url():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e.output}", 500

if __name__ == '__main__':
    app.run(debug=True)