import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route("/", methods=["POST"])
def main():
    payload = request.args.get("payload")

    if not payload:
        return "Missing 'payload' parameter in request", 400

    data = yaml.safe_load(payload)

    if data["type"] == "Create":
        return "Cannot create resource of type 'Create'", 403
    
    return f"Hello {data['name']}!", 200