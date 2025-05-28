import yaml
from flask import Flask, request
app = Flask(__name__)
@app.route("/", methods=["POST"])
def main():
    try:
        payload = yaml.safe_load(request.args.get("payload"))
        if payload["type"] == "Create":
            return "Created"
    except:
        return "Error"
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)