import os
from flask import Flask, request
app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    with open(filename, 'rb') as f:
        return f.read()

if __name__ == "__main__":
    app.run()