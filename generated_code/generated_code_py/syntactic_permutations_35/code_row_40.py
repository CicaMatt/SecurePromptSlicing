from flask import Flask, render_template, request
import os

app = Flask(__name__)

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]

        # check if user exists in the database
        if username and password:
            return render_template("home.html")
        else:
            return render_template("login.html")
    return render_template("login.html")

if __name__ == "__main__":
    app.run(debug=True)