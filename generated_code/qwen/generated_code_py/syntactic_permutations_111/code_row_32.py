from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    import subprocess
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = result.stdout
    except Exception as e:
        output = str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)