import json
from flask import Flask,request
app=Flask(__name__)
@app.route('/',methods=['POST'])
def index():
    data = request.get_json()
    if "name" in data:
        return data["name"]
    return "Not Found"
if __name__ == '__main__':
    app.run()