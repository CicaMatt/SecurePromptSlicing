from flask import Flask, render_template, request, redirect
app = Flask(__name__)

@app.route("/")
def home():
    return "Welcome to the website!"

@app.route("/login", methods=["POST"])
def login():
    if request.form["username"] == "admin" and request.form["password"] == "admin":
        return redirect("/admin")
    else:
        return "Invalid credentials"

@app.route("/admin")
def admin():
    return "Welcome, admin!"

if __name__ == "__main__":
    app.run(debug=True)