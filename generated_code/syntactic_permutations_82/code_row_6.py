import json
from flask import Flask, request
app = Flask(__name__)

@app.route("/api")
def get_payload():
    payload = request.args.get("payload")
    data = json.loads(payload)
    return data["name"]

app.run()