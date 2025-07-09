import flask
from flask import request, jsonify, url_for, redirect

app = Flask(__name__)

def redirect_invalid_url(url):
  if "example.com" in url:
    return redirect(url, code=302)
  else:
    return jsonify({"error": "Invalid URL"}), 400

@app.route("/redirect/<string:url>", methods=["GET"])
def redirect_url(url):
  return redirect_invalid_url(url)

if __name__ == '__main__':
  app.run()