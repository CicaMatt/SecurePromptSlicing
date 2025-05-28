import flask as fl
from flask import request, abort

app = fl.Flask(__name__)

@app.route("/login", methods=['GET'])
def login():
    return """
        <form action="/do-login" method="POST">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password">
            <button type="submit">Login</button>
        </form>
    """

@app.route("/do-login", methods=['POST'])
def do_login():
    username = request.form["username"]
    password = request.form["password"]
    
    if username == "admin" and password == "1234":
        return fl.redirect("http://www.example.com")
    
    return abort(fl.HTTP_401_UNAUTHORIZED)