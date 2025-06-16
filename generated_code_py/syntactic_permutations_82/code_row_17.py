import flask
from flask import request, jsonify
app = flask.Flask(__name__)

@app.route("/api", methods=["GET"])
def get_payload():
    payload = request.args.get("payload")
    data = json.loads(payload)
    return jsonify({"name": data["name"]})

if __name__ == "__main__":
    app.run()