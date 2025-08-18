from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'ping'

@app.route(f'/{url}', methods=['GET'])
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', '127.0.0.1'], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)