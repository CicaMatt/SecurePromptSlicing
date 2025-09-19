from flask import Flask, request

app = Flask(__name__)

@app.route('/<path:url>', methods=['GET'])
def ping(url):
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return f"Requested URL: {url}\nPing Result:\n{result.stdout}"

if __name__ == '__main__':
    app.run(debug=True)