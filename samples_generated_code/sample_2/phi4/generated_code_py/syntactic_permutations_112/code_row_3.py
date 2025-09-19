from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "example.com"  # You can set your desired URL here.

@app.route(f'/{url}/ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)