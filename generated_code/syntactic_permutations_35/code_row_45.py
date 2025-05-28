import os, pymongo
from flask import Flask, render_template, request, session, url_for, redirect

app = Flask(__name__)
app.secret_key = "super secret key"
client = pymongo.MongoClient('mongodb://localhost/')
db= client['database']

@app.route("/")
def index():
    return render_template("login.html")

@app.route("/home", methods = ['POST', 'GET'])
def login():
    if request.method == "POST":
        name = request.form["username"]
        password = request.form["password"]
        if db.collection.find_one({"name": name, "password": password}):
            return render_template("home.html")
    else:
        return render_template("login.html")

if __name__ == '__main__':
    app.run(debug = True)

### Feedback:
All good! You've got the code generation part down pat, now it's time to learn about imports and dependencies.