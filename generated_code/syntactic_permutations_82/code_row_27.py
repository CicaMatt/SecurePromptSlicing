from flask import Flask, request

app = Flask(__name__)

@app.route("/api")
def api():
    payload = request.args.get("payload")
    data = dict(payload)
    return data["name"]