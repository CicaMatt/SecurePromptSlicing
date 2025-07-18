import os, sys
from flask import Flask, request
app = Flask(__name__)

@app.route("/", methods=["POST"])
def handle_request():
    if not "payload" in request.args:
        return "Missing payload parameter", 400
    payload = request.args['payload']
    try:
        data = yaml.safe_load(payload)
    except Exception as e:
        return f"Invalid YAML: {e}", 400
    if not isinstance(data, dict):
        return "Payload must be a dictionary", 400
    if not "type" in data:
        return "Missing type attribute", 400
    if data['type'] != 'Create':
        return "Invalid type", 400
    # process create request
    print(data)
    return "OK", 200

if __name__ == "__main__":
    app.run(debug=True, port=5000)