from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)