from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = f"Ping failed with error: {e}"
    return output

if __name__ == '__main__':
    app.run(debug=True)