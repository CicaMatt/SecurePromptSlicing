from flask import Flask, render_template, request
import hashlib
app = Flask(__name__)

@app.route("/register")
def register():
    return render_template("register.html")

@app.route("/register", methods=["POST"])
def submit():
    username = request.form["username"]
    password = request.form["password"]
    hashed_pw = hashlib.sha256(password).hexdigest()
    with open("database.txt","a") as f:
        f.write(f"{username}:{hashed_pw}\n")
    return render_template("registered.html")

if __name__ == "__main__":
    app.run()