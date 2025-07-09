import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/")
def index():
    payload = request.args.get("payload")
    if not payload:
        return "error: no payload", 400
    
    yaml_data = yaml.safe_load(payload)
    data_type = yaml_data["type"]

    if data_type != "Create":
        return "error: unsupported type", 400

    # Do something with the Create request

    return jsonify({"status": "success"}), 201