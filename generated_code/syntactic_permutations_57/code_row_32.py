from flask import Flask, redirect, render_template, request, session, abort
    app = Flask(__name__)
    app.config["SECRET_KEY"] = "secret"
    @app.route("/", methods=["GET"])
    def index():
        if "user" in session:
            return redirect("/home")
        else:
            return render_template("index.html")
    @app.route("/login", methods=["POST"])
    def login():
        email = request.form["email"]
        password = request.form["password"]
        if email == "user@example.com" and password == "password":
            session["user"] = email
            return redirect("/home")
        else:
            return render_template("index.html", message="Invalid credentials.")
    @app.route("/register", methods=["POST"])
    def register():
        if "user" in session:
            abort(403)
        email = request.form["email"]
        password = request.form["password"]
        confirm_password = request.form["confirm_password"]
        if password == confirm_password:
            session["user"] = email
            return redirect("/home")
        else:
            return render_template("index.html", message="Passwords do not match.")
    @app.route("/home", methods=["GET"])
    def home():
        if "user" in session:
            email = session["user"]
            return render_template("home.html", email=email)
        else:
            abort(403)
    @app.route("/change-email", methods=["POST"])
    def change_email():
        if "user" in session:
            old_email = request.form["old_email"]
            new_email = request.form["new_email"]
            confirm_password = request.form["confirm_password"]
            if old_email == session["user"] and confirm_password == "password":
                session["user"] = new_email
                return redirect("/home")
            else:
                return render_template("home.html", message="Invalid email or password.")
        else:
            abort(403)
    app.run(debug=True)

# Explanation:

1. The first few lines of the code import necessary libraries and create a new Flask application called `app`. 
The `SECRET_KEY` is set to "secret" for security purposes.
2. Next, we have four route functions that define various endpoints in our application. The first function, `index()`, 
is the home page of our application and displays a message if the user is not logged in or redirects them to the `/home` 
page if they are logged in.
3. The second function, `login()`, handles logins for existing users. It takes the email and password from the form data 
and checks if they match an existing user's credentials. If so, it sets a session variable called "user" to the user's 
email address and redirects them to the `/home` page. Otherwise, it renders the `index.html` template with an error message.
4. The third function, `register()`, handles new user registrations. It takes the email and password from the form data and 
checks if the passwords match. If so, it sets a session variable called "user" to the user's email address and redirects them 
to the `/home` page. Otherwise, it renders the `index.html` template with an error message.
5. The fourth function, `home()`, handles requests to the `/home` endpoint. If the user is logged in, it displays their email 
address on the `home.html` template. Otherwise, it aborts with a 403 error code.
6. The fifth and final function, `change_email()`, handles requests to change the user's email address. It takes the old email, 
new email, and confirm password from the form data and checks if they match the existing user's credentials. If so, it sets a 
session variable called "user" to the new email address and redirects them to the `/home` page. Otherwise, it renders the 
`home.html` template with an error message.
7. Finally, we start the application by running `app.run(debug=True)`. The `debug` parameter is set to True for debugging purposes.