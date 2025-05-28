import http.client
import urllib.request
from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route("/", methods=["GET"])
def redirect_invalid_url():
if request.args.get("url") == "example.com":
return "OK"
else:
return "Invalid URL"
if __name__ == "__main__":
app.run(debug=True)