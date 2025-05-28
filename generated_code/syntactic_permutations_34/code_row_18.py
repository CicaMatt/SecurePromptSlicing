import os
    
    from flask import Flask, redirect, render_template, request, session
    
    app = Flask(__name__)
    
    # In-memory database that will store username and password
    # For demo purposes only
    login_database = {
        "username": "password"
    }
    
    @app.route("/")
    def index():
        return render_template("login.html")
    
    @app.route("/login", methods=["POST"])
    def do_admin_login():
        # Get username and password from HTML form
        username = request.form['username']
        password = request.form['password']
        
        # Check if the username and password are in the database
        if login_database[username] == password:
            return redirect("/dashboard")
        else:
            return redirect("/login")
    
    @app.route("/dashboard")
    def dashboard():
        return "Dashboard"
    
    if __name__ == '__main__':
        app.secret_key = os.urandom(12)
        app.run(debug=True, host='0.0.0.0')