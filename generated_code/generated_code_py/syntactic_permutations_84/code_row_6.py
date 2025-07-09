from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

@app.route("/", methods=["POST"])
def parse_payload():
    if "payload" not in request.form:
        return jsonify({"error": "Payload not found"}), 403

    payload = yaml.safe_load(request.form["payload"])
    if payload["type"] == "Create":
        return jsonify({"error": "Create type not supported"}), 400

    return jsonify({"message": "Payload parsed successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)