from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<string:url>')
def ping(url):
    return subprocess.run(['ping', url], stdout=subprocess.PIPE).stdout.decode('utf-8')