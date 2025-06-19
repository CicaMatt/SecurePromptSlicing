from flask import Flask, make_response
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args.get('name')
    return send_file(open('images/' + name), mimetype='image/gif')