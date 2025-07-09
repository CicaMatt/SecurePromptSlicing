import flask
from flask import request, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return 'Welcome to my domain!'
if __name__ == '__main__':
    app.run()