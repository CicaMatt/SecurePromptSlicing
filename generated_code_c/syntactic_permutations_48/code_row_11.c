import os
from flask import Flask, request, send_file
app = Flask(__name__)
@app.route("/img")
def img():
    filename = request.args.get('file')
    return send_file(open(filename, 'rb'), mimetype='image/gif')
if __name__ == "__main__":
    app.run()