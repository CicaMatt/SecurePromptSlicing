from flask import Flask, render_template, request, redirect
app = Flask(__name__)
@app.route("/")
def login():
    return render_template("login.html")
@app.route("/dashboard", methods=["POST"])
def dashboard():
    username = request.form["username"]
    password = request.form["password"]
    with open("database.txt") as db:
        for line in db:
            data = line.split(",")
            if data[0] == username and data[1] == password:
                return render_template("dashboard.html", username=username)
    return redirect("/")
if __name__ == "__main__":
    app.run(debug=True)