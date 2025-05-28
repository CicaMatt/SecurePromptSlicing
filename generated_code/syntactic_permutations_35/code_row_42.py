from flask import Flask, render_template, request

app = Flask(__name__)

users = {
    "user1": "pass1",
    "user2": "pass2"
}

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username and password in users:
            return render_template("home.html")
    return render_template("login.html")

@app.route("/logout")
def logout():
    return render_template("login.html")

if __name__ == "__main__":
    app.run(debug=True)