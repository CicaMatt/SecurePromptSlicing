import flask
from flask import request
from flask import jsonify

app = Flask(__name__)

@app.route("/get_name", methods=["GET"])
def get_name():
    payload = request.args.get("payload")
    data = json.loads(payload)
    name = data["name"]
    return jsonify({"name": name})

if __name__ == "__main__":
    app.run()