from flask import Flask, request
import subprocess

app = Flask(__name__)
url = ""

@app.route('/ping', methods=['GET'])
def ping():
    global url
    url = request.args.get('url', '')
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        return f"Ping result for {url}:<br>{output.decode()}"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)