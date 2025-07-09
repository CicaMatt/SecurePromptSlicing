import json
from flask import Flask, request
app = Flask(__name__)
@app.route("/")
def main():
    return "Welcome!"
@app.route("/get_name", methods=["GET"])
def get_name():
    payload = request.args.get("payload")
    data = json.loads(payload)
    name = data["name"]
    return name
if __name__ == "__main__":
    app.run()