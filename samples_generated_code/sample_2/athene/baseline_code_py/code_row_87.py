from flask import Flask, request
import subprocess

app = Flask(__name__)
url = ""

@app.route('/ping', methods=['GET'])
def ping():
    global url
    url = request.args.get('url', '')
    try:
        result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)