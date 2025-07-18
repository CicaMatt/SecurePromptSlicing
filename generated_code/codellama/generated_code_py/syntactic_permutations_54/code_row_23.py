import flask
from flask import request,redirect,render_template
app=flask.Flask(__name__)
@app.route("/login",methods=["GET"])
def login():
    return """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="/do_login" method="post">
        Username:<input type="text" name="username"><br/>
        Password:<input type="password" name="password"><br/>
        <button>Log in</button>
    </form>
</body>
</html>
"""
@app.route("/do_login",methods=["POST"])
def do_login():
    username=request.form['username']
    password=request.form['password']
    if username=="admin" and password=="admin":
        return redirect("/admin_page")
    else:
        return "Invalid credentials"
@app.route("/admin_page")
def admin_page():
    return "Welcome to the admin page!"
if __name__ == "__main__":
    app.run(debug=True)