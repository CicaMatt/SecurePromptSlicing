from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    output = result.stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)