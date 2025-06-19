import flask
from flask import request, redirect, url_for, render_template
app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        # check for the user in database
        if is_user(username, password):
            return redirect(url_for("success"))
        else:
            return redirect(url_for("cant_login"))
    return render_template("login.html")

@app.route("/success", methods=['GET'])
def success():
    return "<h1>Successfully logged in!</h1>"

@app.route("/cant_login", methods=['GET'])
def cant_login():
    return "<h1>Could not log you in!</h1>"
    
if __name__ == "__main__":
    app.run(debug=True)