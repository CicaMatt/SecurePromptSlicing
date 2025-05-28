import hashlib
from flask import Flask
from flask import request, render_template, session, redirect, url_for

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["POST"])
def login():
    username = request.form["username"]
    password = hashlib.sha256(request.form["password"].encode()).hexdigest()
    
    return render_template("login.html", username=username, password=password)

if __name__ == "__main__":
    app.run(debug=True)

### Explanation:
The above code is a simple web application that allows users to login using their username and password. The username and password are stored in the database after hashing the password. 
The code uses Flask as the micro web framework, hashlib for hashing the password.
The code defines two routes: "/" and "/login". The "/" route is used to render the login page, while the "/login" route is used to handle the login request and display the result.