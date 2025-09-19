from flask import Flask, request

app = Flask(__name__)

url = "example.com"

@app.route('/ping', methods=['GET'])
def ping():
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return f"Ping results for {url}:\n{result.stdout}"

if __name__ == '__main__':
    app.run(debug=True)