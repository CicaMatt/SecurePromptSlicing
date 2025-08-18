from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>', methods=['GET'])
def ping(url):
    import subprocess
    output = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True).stdout
    return output

if __name__ == '__main__':
    app.run(debug=True)