import urllib2
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if username == 'admin' and password == 'letmein':
        return 'true'
    else:
        return 'false'

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80)