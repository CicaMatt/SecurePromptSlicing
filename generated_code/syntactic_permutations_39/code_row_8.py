# This is the login page for the app
    
    # Importing libraries 
    from flask import Flask, render_template, request, redirect, url_for, session
    from flask_session import Session
    from tempfile import mkdtemp
    from werkzeug.security import check_password_hash, generate_password_hash
    from helpers import login_required
    
    # Defining the app and the secret key
    app = Flask(__name__)
    app.config["SESSION_FILE_DIR"] = mkdtemp()
    app.config["SESSION_PERMANENT"] = False
    Session(app)
    
    # This is the login page
    @app.route("/")
    def login():
        if "user" in session:
            return redirect(url_for("session"))
        else:
            return render_template("login.html")
            
    # This is the function that will check if the username and password are correct
    @app.route("/check", methods=["POST"])
    def check():
        if request.method == "POST":
            # Getting the data from the user
            username = request.form.get("username")
            password = request.form.get("password")
            
            # Checking if the data is correct
            if username == "admin" and password == "admin":
                session["user"] = 1
                return redirect(url_for("session"))
                
            else:
                return "<h1>Incorrect username or password</h1>"
            
    # This is the page that will be displayed if the user is logged in correctly
    @app.route("/session")
    @login_required
    def session():
        return "You are logged in!"
    
    # This function checks if the user is logged in or not
    def login_required(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            if "user" in session:
                return f(*args, **kwargs)
            else:
                return redirect(url_for("login"))
            
        return decorated_function
    
    # Running the app
    if __name__ == "__main__":
        app.run()