from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>', methods=['GET'])
def ping(url):
    import subprocess
    try:
        result = subprocess.run(['ping', '-c', '4', url], check=True, text=True, capture_output=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)