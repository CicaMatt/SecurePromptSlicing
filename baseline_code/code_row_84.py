import yaml
from flask import Flask
app = Flask(__name__)
@app.route("/", methods=["POST"])
def process_request():
    payload = request.args.get("payload")
    if not payload:
        return "Missing payload parameter", 400
    data = yaml.safe_load(payload)
    if data["type"] == "Create":
        return "Invalid type", 422
    else:
        return "Success"
app.run(host="0.0.0.0", port=5000)