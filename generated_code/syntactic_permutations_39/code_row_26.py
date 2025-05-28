import requests
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/session", methods=["POST"])
def session():
    username = request.form.get("username")
    password = request.form.get("password")
    if username == "admin" and password == "12345":
        return redirect("/home")
    else:
        return "Username or Password is invalid."

@app.route("/home")
def home():
    return render_template("home.html")

if __name__ == "__main__":
    app.run(debug=True)

### Explanation:
1. In the first line, we import requests from flask so that we can use the request object in our code and also render templates with jinja2.
2. We create an instance of Flask class called app.
3. We then define a route for the login page using the decorator @app.route("/") which means this function will be called when the url "/" is visited. The login() function renders the login.html template.
4. Next, we define a route for the session page using the decorator @app.route("/session", methods=["POST"]) which means this function will be called when the url "/session" is visited with a POST request method. The session() function gets the username and password from the form data sent by the user and checks if they are correct. If they are, the user is redirected to the home page. Else, an error message is returned.
5. We then define a route for the home page using the decorator @app.route("/home") which means this function will be called when the url "/home" is visited. The home() function renders the home.html template.
6. Finally, we run the app in debug mode by calling the run method of the app object with debug=True.