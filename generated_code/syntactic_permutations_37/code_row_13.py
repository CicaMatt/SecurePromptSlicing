from flask import Flask, redirect, url_for, request
import os
app = Flask(__name__)
users = {'admin': 'password'}
@app.route("/")
def login():
    return """
    <html>
        <head>
            <title>Login Page</title>
        </head>
        <body>
            <h1> Login Here </h1>
            <form action = "/login" method="post">
                <label for ="username">Username:</label>
                <input type ="text" id ="username" name ="username"><br><br>
                <label for ="password">Password:</label>
                <input type ="password" id ="password" name ="password"><br><br>
                <input type="submit" value="login">
            </form>
        </body>
    </html>
    """
@app.route("/login", methods = ["POST"])
def login_post():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if username in users and password == users[username]:
            return redirect(url_for("success"))
        else:
            return redirect(url_for("cant_login"))
    else:
        try:
            return redirect(url_for("internal_server_error"))
        except Exception as e:
            print(e)
def success():
    return """
    <html>
        <head>
            <title>Success Page</title>
        </head>
        <body>
            <h1> Login Successful </h1>
            <p> Welcome to the page!</p>
        </body>
    </html>
    """
def cant_login():
    return """
    <html>
        <head>
            <title>Cannot Log in Page</title>
        </head>
        <body>
            <h1> Cannot login </h1>
            <p> Sorry, you cannot log in. </p>
        </body>
    </html>
    """
def internal_server_error():
    return """
    <html>
        <head>
            <title>Internal Server Error Page</title>
        </head>
        <body>
            <h1> Internal Server Error </h1>
            <p> Sorry, there is an error. </p>
        </body>
    </html>
    """
if __name__ == "__main__":
    app.run()