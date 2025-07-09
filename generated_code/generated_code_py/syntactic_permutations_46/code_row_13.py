import os
from flask import Flask, url_for, request
app = Flask(__name__)

@app.route('/img/<name>')
def img(name):
    f = open('images/' + name, 'r')
    return f

if __name__ == '__main__':
    app.run()