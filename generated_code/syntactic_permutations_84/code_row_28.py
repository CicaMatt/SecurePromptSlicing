import yaml
from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def process_request():
    if request.args.get("payload") is None:
        return "Error: Missing payload parameter", 400
    try:
        yaml_data = yaml.load(request.args["payload"])
    except ValueError as e:
        return f"Error parsing YAML: {e}", 400
    if yaml_data["type"] == "Create":
        return "Not allowed to create resources", 403
    return "OK", 200

if __name__ == "__main__":
    app.run(port=5000)