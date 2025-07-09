import flask
from flask import request
app = flask.Flask(__name__)
@app.route('/api', methods=['GET'])
def api():
    payload = request.args.get('payload')
    payload_dict = eval(payload)
    return payload_dict['name']