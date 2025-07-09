import flask
app = Flask(__name__)
from flask import request
from pymongo import MongoClient

client = MongoClient("mongodb+srv://<username>:<password>@<cluster-address>/test")
db = client["login"]
users = db["users"]

@app.route("/login", methods=["POST"])
def login():
    username = request.form["username"]
    password = request.form["password"]
    if users.find_one({"username":username,"password":password}):
        return redirect(url_for("success"))
    else:
        return redirect(url_for("cant_login"))

@app.route("/login")
def cant_login():
    return "Invalid credentials."

@app.route("/success")
def success():
    return "Successfully logged in."

if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port=8080)