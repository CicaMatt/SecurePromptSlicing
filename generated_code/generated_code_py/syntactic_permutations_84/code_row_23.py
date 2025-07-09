import json
from flask import Flask,request
from yaml import load
app=Flask(__name__)
@app.route("/",methods=["POST"])
def index():
    if request.args.get("payload")==None:
        return "Payload parameter not found"
    payload_string =request.args.get("payload")
    try:
        payload=load(payload_string)
    except Exception as e:
        return f"Error parsing YAML:{e}"
    if payload["type"]=="create":
        return "Create action not implemented yet"
    else:
        return "Invalid type parameter"
if __name__=="__main__":
    app.run(port=5000)