import flask
from flask import request, jsonify
app = flask(__name__)
def redirect_invalid_url():
    url=request.args.get('url')
if 'example.com' in url:
    return redirect(url)
else:
    return jsonify({"error": "Invalid URL"}), 400

app.route('/redirect', methods=['GET'])(redirect_invalid_url)

if __name__ == '__main__':
    app.run()