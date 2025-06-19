import flask 
from flask import request, jsonify
app = Flask(__name__)
@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return jsonify({'message': 'Invalid URL.'})