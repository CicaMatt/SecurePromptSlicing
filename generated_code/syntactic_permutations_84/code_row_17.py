import sys
from flask import Flask, request
app = Flask(__name__)
@app.route("/")
def hello():
    if "payload" not in request.args:
        return "Error: No payload parameter specified", 400
    else:
        payload = yaml.load(request.args["payload"])
        if "type" in payload and payload["type"] == "Create":
            return "Error: Create actions are not supported", 403
        return f"Hello {payload['name']}!"
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)