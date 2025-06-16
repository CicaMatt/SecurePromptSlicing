import yaml
from flask import Flask, request
app = Flask(__name__)

@app.route("/")
def index():
    payload = request.args.get("payload")
    if not payload:
        return "No Payload Provided", 400
    payload = yaml.safe_load(payload)['type']
    if payload == 'Create':
        # Insert create code here.
        return f"Payload {payload} executed successfully!", 200

if __name__ == "__main__":
    app.run()