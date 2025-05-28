import flask
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route("/")
def login():
    form = LoginForm()
    if request.method == "POST":
        name = form.name.data
        password = form.password.data
        user = User(name, password)
        return redirect(url_for("do_login"))
    else:
        return render_template("login.html", form=form)

@app.route("/admin", methods=["GET", "POST"])
def do_login():
    if request.method == "POST":
        name = request.form["name"]
        password = request.form["password"]
        user = User(name, password)
        if user.is_admin() == True:
            return render_template("index.html")
        else:
            return redirect(url_for("login"))
    else:
        return render_template("login.html", form=form)

if __name__ == "__main__":
    app.run()