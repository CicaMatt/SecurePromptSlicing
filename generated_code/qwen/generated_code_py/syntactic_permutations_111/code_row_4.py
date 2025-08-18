from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = e.output.decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)