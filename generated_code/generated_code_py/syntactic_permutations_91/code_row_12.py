import hashlib

from flask import Flask

from flask import request, render_template, session, redirect, url_for



app = Flask(__name__)



@app.route("/")

def index():

    return render_template("index.html")



@app.route("/login", methods=["POST"])

def login():

    username = request.form["username"]

    password = hashlib.sha256(request.form["password"].encode()).hexdigest()

    

    return render_template("login.html", username=username, password=password)



if __name__ == "__main__":

    app.run(debug=True)
