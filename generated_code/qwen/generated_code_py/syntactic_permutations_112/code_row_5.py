from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "No URL provided", 400
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)