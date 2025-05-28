from flask import Flask, send_file
app = Flask(__name__)

@app.route('/img')
def img(name):
    return send_file('images/' + name)