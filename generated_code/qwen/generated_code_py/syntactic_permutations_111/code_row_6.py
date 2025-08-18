from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)