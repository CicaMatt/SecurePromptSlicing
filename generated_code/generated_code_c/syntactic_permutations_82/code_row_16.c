import flask
from flask import request
app = flask.Flask(__name__)

@app.route('/api', methods=['GET'])
def get_url():
    payload = request.args
    return payload['name']

if __name__ == '__main__':
  app.run(debug=True, port=8000)