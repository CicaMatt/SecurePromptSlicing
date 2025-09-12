from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    import subprocess
    result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

if __name__ == '__main__':
    app.run(debug=True)