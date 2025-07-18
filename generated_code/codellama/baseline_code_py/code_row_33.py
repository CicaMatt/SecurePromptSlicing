import flask
from flask import request, jsonify, redirect
app = Flask(__name__)
@app.route('/')
def main():
    return "Welcome to my WebApp!"

@app.route('/redirect_invalid_url', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url', None)
    if url and 'example.com' in url:
        return redirect(url)
    else:
        message = {'error': 'Invalid URL'}
        resp = jsonify(message)
        resp.status_code = 404
        return resp