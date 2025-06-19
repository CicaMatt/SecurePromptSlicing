import hashlib
from flask import Flask, request, session, redirect, url_for, render_template
app = Flask(__name__)
app.config["SECRET_KEY"] = "super-secret"
@app.route("/")
def index():
    return render_template("index.html")
@app.route("/register", methods=["POST"])
def register():
    username = request.form["username"]
    password = hashlib.sha256(request.form["password"].encode()).hexdigest()
    # insert into database
    return redirect(url_for("index"))
if __name__ == "__main__":
    app.run(debug=True)