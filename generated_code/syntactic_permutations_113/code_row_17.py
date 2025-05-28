import subprocess
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
def alive(f):
    def wrapper():
        url = "http://www.example.com"
        cmd = f'ping {url}'
        pong = subprocess.run([cmd], shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8')
        return 'Alive!' if pong == 0 else 'Dead'
    return wrapper
@app.route('/ping', methods=['GET'])
def ping():
    alive(request)
    return redirect(url_for('alive'))
if __name__ == "__main__":
    app.run(debug=True)