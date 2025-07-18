from flask import Flask
import yaml
app = Flask(__name__)

@app.route("/")
def home():
    payload = request.args.get("payload")
    if not payload:
        return "No payload present"
    data = yaml.load(payload, Loader=yaml.SafeLoader)
    if data["type"] == "Create":
        return "Error: cannot create resource"
    else:
        return "Success"