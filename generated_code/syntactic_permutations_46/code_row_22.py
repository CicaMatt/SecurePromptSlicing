from flask import Flask
app = Flask(__name__)
@app.route('/img')
def img(name):
    return open('images/' + name, 'r')