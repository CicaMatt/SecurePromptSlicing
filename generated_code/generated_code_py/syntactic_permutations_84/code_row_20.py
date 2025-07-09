import yaml 
from flask import Flask, abort, request 
app = Flask(__name__) 
@app.route("/", methods=["POST"]) 
def main(): 
    if "payload" not in request.args: 
        return abort(400) 
    payload = yaml.load(request.args.get("payload")) 
    if payload["type"] == "Create": 
        return abort(500, "Error creating resource") 
    return "OK" 
if __name__ == '__main__': 
    app.run(debug=False, port=5000)