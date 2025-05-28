from flask import Flask, request
app = Flask(__name__)
@app.route('/img/<file>')
def img():
    return open(request.args.get('file'))