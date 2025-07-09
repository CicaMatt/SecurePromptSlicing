import sys
from flask import Flask, request, jsonify
from yaml import load, FullLoader
app = Flask(__name__)
@app.route("/", methods=["POST"])
def process_request():
    payload = request.args.get("payload")
    if not payload:
        return "Invalid Request"
    data = load(payload, Loader=FullLoader)
    if data["type"] == "Create":
        return "Not Implemented"
    else:
        return jsonify({"result": "Success"})
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)